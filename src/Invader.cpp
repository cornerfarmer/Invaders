#include "Invader.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp" 
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include "World.hpp"

Invader::Invader(World* world_, sf::Vector2i pos_, const LightBulb::FeedForwardNetworkTopologyOptions& networkTopologyOptions)
	:AbstractGameObject(pos_, 4), LightBulb::AbstractDefaultReinforcementIndividual(world_, networkTopologyOptions, true)
{
	world = world_;
	dir = LEFT;
	marked = false;
}

void Invader::draw(sf::RenderWindow& window, sf::Vector2i offset)
{
	if (!dead) 
	{
		drawTile(window, world->getMap(), getPos(), marked ? sf::Color::Blue : sf::Color::Red, offset);

		sf::RectangleShape rectHead(sf::Vector2f(world->getMap().getTileSize().x * 0.6, world->getMap().getTileSize().y * 0.2));
		rectHead.setPosition(world->getMap().getTileSize().x * getPos().x + 0.2 * world->getMap().getTileSize().x + offset.x, world->getMap().getTileSize().y * getPos().y + offset.y);

		sf::Transform transform;
		transform.rotate(dir * 90, sf::Vector2f(world->getMap().getTileSize().x * getPos().x + world->getMap().getTileSize().x / 2 + offset.x, world->getMap().getTileSize().y * getPos().y + world->getMap().getTileSize().y / 2 + offset.y));

		rectHead.setFillColor(sf::Color::Yellow);

		window.draw(rectHead, transform);
	}
}


void Invader::interpretNNOutput(LightBulb::Vector<char>& output)
{
	lastPos = getPos();
	if (output.getEigenValue()[0])
		walk(*world, dir);
	else if (output.getEigenValue()[1])
		walk(*world, static_cast<Direction>((dir + 1) % 4));
	else if (output.getEigenValue()[2])
		walk(*world, static_cast<Direction>((dir + 2) % 4));
	else if(output.getEigenValue()[3])
		walk(*world, static_cast<Direction>((dir + 3) % 4));
}

void Invader::getNNInput(LightBulb::Vector<>& input) const
{
	sf::Vector2i dirVector = getDirVector();
	sf::Vector2i rotatedDirVector(-dirVector.y, dirVector.x);

	int inputIndex = 0;
	for (int i = 2; i >= -2; i--)
	{
		for (int j = 2; j >= -2; j--)
		{
			if (i != 0 || j != 0)
				input.getEigenValueForEditing()[inputIndex++] = world->getTileValue(getPos() + i * dirVector + j * -rotatedDirVector);
		}
	}

	input.getEigenValueForEditing()[inputIndex++] = dir == DOWN || dir == LEFT ? 1 : 0;
	input.getEigenValueForEditing()[inputIndex++] = dir == RIGHT || dir == LEFT ? 1 : 0;

	input.getEigenValueForEditing()[inputIndex++] = (float)getPos().x / world->getMap().getWidth();
	input.getEigenValueForEditing()[inputIndex++] = (float)getPos().y / world->getMap().getHeight();
}

void Invader::isTerminalState(LightBulb::Scalar<char>& isTerminalState) const
{
	isTerminalState.getEigenValueForEditing() = world->getTime() == 20 || dead;
}

void Invader::getReward(LightBulb::Scalar<>& reward) const
{
	if (dead && getPos().x != 0)
		reward.getEigenValueForEditing() = -2;
	else
		reward.getEigenValueForEditing() = lastPos.x - getPos().x;
}

void Invader::setMarked(bool marked_)
{
	marked = marked_;
}

bool Invader::doStep()
{
	doSimulationStep();
	return true;
}
