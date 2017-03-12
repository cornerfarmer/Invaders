#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp"

Player::Player(Map* map_, sf::Vector2i pos_)
	:AbstractGameObject(pos_, 4)
{
	map = map_;
	dir = RIGHT;
}

void Player::draw(sf::RenderWindow& window, sf::Vector2i offset)
{
	drawTile(window, *map, getPos(), sf::Color::Red, offset);

	sf::RectangleShape rectHead(sf::Vector2f(map->getTileSize().x * 0.6, map->getTileSize().y * 0.2));
	rectHead.setPosition(map->getTileSize().x * getPos().x + 0.2 * map->getTileSize().x + offset.x, map->getTileSize().y * getPos().y + offset.y);

	sf::Transform transform;
	transform.rotate(dir * 90, sf::Vector2f(map->getTileSize().x * getPos().x + map->getTileSize().x / 2 + offset.x, map->getTileSize().y * getPos().y + map->getTileSize().y / 2 + offset.y));
	
	rectHead.setFillColor(sf::Color::Yellow);

	window.draw(rectHead, transform);
}

bool Player::doStep()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		walk(*map, LEFT);
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		walk(*map, RIGHT);
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		walk(*map, UP);
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		walk(*map, DOWN);
		return true;
	}
	return false;
}
