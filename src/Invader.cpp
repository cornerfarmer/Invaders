#include "Invader.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp" 
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>

Invader::Invader(Map* map_, sf::Vector2i pos_, const LightBulb::FeedForwardNetworkTopologyOptions& networkTopologyOptions)
	:AbstractGameObject(pos_), LightBulb::AbstractDefaultReinforcementIndividual(map, networkTopologyOptions, true, 0)
{
	map = map_;
	dir = LEFT;
}

void Invader::draw(sf::RenderWindow& window)
{
	drawTile(window, *map, getPos(), sf::Color::Red);

	sf::RectangleShape rectHead(sf::Vector2f(map->getTileSize().x * 0.6, map->getTileSize().y * 0.2));
	rectHead.setPosition(map->getTileSize().x * getPos().x + 0.2 * map->getTileSize().x, map->getTileSize().y * getPos().y);

	sf::Transform transform;
	transform.rotate(dir * 90, sf::Vector2f(map->getTileSize().x * getPos().x + map->getTileSize().x / 2, map->getTileSize().y * getPos().y + map->getTileSize().y / 2));
	
	rectHead.setFillColor(sf::Color::Yellow);

	window.draw(rectHead, transform);
}


void Invader::interpretNNOutput(LightBulb::Vector<char>& output)
{
	sf::Vector2i newPos = getPos();
	newPos.x--;
	setPos(newPos, *map);
}

void Invader::getNNInput(LightBulb::Vector<>& input) const
{

}

void Invader::isTerminalState(LightBulb::Scalar<char>& isTerminalState) const
{

}

void Invader::getReward(LightBulb::Scalar<>& reward) const
{

}
