#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Player::Player(Map* map_, int posX_, int posY_)
{
	map = map_;
	posX = posX_;
	posY = posY_;
}

void Player::draw(sf::RenderWindow& window, sf::Vector2f tileSize)
{
	sf::RectangleShape rect(tileSize);
	rect.setPosition(tileSize.x * posX, tileSize.y * posY);

	rect.setFillColor(sf::Color::Red);

	window.draw(rect);
}


int Player::getX()
{
	return posX;
}

int Player::getY()
{
	return posY;
}

void Player::processEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
			posX--;
		if (event.key.code == sf::Keyboard::Right)
			posX++;
		if (event.key.code == sf::Keyboard::Up)
			posY--;
		if (event.key.code == sf::Keyboard::Down)
			posY++;
	}
}
