#include "Invader.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp" 
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>

Invader::Invader(Map* map_, sf::Vector2i pos_, const LightBulb::FeedForwardNetworkTopologyOptions& networkTopologyOptions)
	:AbstractGameObject(pos_), LightBulb::AbstractDefaultReinforcementIndividual(map, networkTopologyOptions, true)
{
	map = map_;
	dir = RIGHT;
}

void Invader::draw(sf::RenderWindow& window)
{
	if (!dead) 
	{
		drawTile(window, *map, getPos(), sf::Color::Red);

		sf::RectangleShape rectHead(sf::Vector2f(map->getTileSize().x * 0.6, map->getTileSize().y * 0.2));
		rectHead.setPosition(map->getTileSize().x * getPos().x + 0.2 * map->getTileSize().x, map->getTileSize().y * getPos().y);

		sf::Transform transform;
		transform.rotate(dir * 90, sf::Vector2f(map->getTileSize().x * getPos().x + map->getTileSize().x / 2, map->getTileSize().y * getPos().y + map->getTileSize().y / 2));

		rectHead.setFillColor(sf::Color::Yellow);

		window.draw(rectHead, transform);
	}
}


void Invader::interpretNNOutput(LightBulb::Vector<char>& output)
{
	lastPos = getPos();
	if (output.getEigenValue()[0])
		walk(*map, dir);
	else if (output.getEigenValue()[1])
		walk(*map, static_cast<Direction>((dir + 1) % 4));
	else if (output.getEigenValue()[2])
		walk(*map, static_cast<Direction>((dir + 2) % 4));
	else if(output.getEigenValue()[3])
		walk(*map, static_cast<Direction>((dir + 3) % 4));
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
				input.getEigenValueForEditing()[inputIndex++] = map->isTileWalkable(getPos() + i * dirVector + j * rotatedDirVector);
		}
	}

	input.getEigenValueForEditing()[inputIndex++] = dir == DOWN || dir == LEFT ? 1 : 0;
	input.getEigenValueForEditing()[inputIndex++] = dir == RIGHT || dir == LEFT ? 1 : 0;

	input.getEigenValueForEditing()[inputIndex++] = map->getTime() / 10.0;
}

void Invader::isTerminalState(LightBulb::Scalar<char>& isTerminalState) const
{
	isTerminalState.getEigenValueForEditing() = map->getTime() == 20;
}

void Invader::getReward(LightBulb::Scalar<>& reward) const
{
	if (dead)
		reward.getEigenValueForEditing() = -2;
	else
		reward.getEigenValueForEditing() = lastPos.x - getPos().x;
}
