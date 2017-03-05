#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp"

Player::Player(Map* map_, sf::Vector2i pos_)
	:AbstractGameObject(pos_)
{
	map = map_;
	dir = RIGHT;
}

void Player::draw(sf::RenderWindow& window)
{
	drawTile(window, *map, getPos(), sf::Color::Red);

	sf::RectangleShape rectHead(sf::Vector2f(map->getTileSize().x * 0.6, map->getTileSize().y * 0.2));
	rectHead.setPosition(map->getTileSize().x * getPos().x + 0.2 * map->getTileSize().x, map->getTileSize().y * getPos().y);

	sf::Transform transform;
	transform.rotate(dir * 90, sf::Vector2f(map->getTileSize().x * getPos().x + map->getTileSize().x / 2, map->getTileSize().y * getPos().y + map->getTileSize().y / 2));
	
	rectHead.setFillColor(sf::Color::Yellow);

	window.draw(rectHead, transform);
}

void Player::processEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			walk(*map, LEFT);
		}
		if (event.key.code == sf::Keyboard::Right)
		{
			walk(*map, RIGHT);
		}
		if (event.key.code == sf::Keyboard::Up)
		{
			walk(*map, UP);
		}
		if (event.key.code == sf::Keyboard::Down)
		{
			walk(*map, DOWN);
		}
	}
}
