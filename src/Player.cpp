#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp"
#include "World.hpp"

Player::Player(World* world_, sf::Vector2i pos_)
	:AbstractGameObject(pos_, 4)
{
	world = world_;
	dir = RIGHT;
}

void Player::draw(sf::RenderWindow& window, sf::Vector2i offset)
{
	drawTile(window, world->getMap(), getPos(), sf::Color::Red, offset);

	sf::RectangleShape rectHead(sf::Vector2f(world->getMap().getTileSize().x * 0.6, world->getMap().getTileSize().y * 0.2));
	rectHead.setPosition(world->getMap().getTileSize().x * getPos().x + 0.2 * world->getMap().getTileSize().x + offset.x, world->getMap().getTileSize().y * getPos().y + offset.y);

	sf::Transform transform;
	transform.rotate(dir * 90, sf::Vector2f(world->getMap().getTileSize().x * getPos().x + world->getMap().getTileSize().x / 2 + offset.x, world->getMap().getTileSize().y * getPos().y + world->getMap().getTileSize().y / 2 + offset.y));
	
	rectHead.setFillColor(sf::Color::Yellow);

	window.draw(rectHead, transform);
}

bool Player::doStep()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		walk(*world, LEFT);
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		walk(*world, RIGHT);
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		walk(*world, UP);
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		walk(*world, DOWN);
		return true;
	}
	return false;
}
