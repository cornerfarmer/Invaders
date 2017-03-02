#include "Wall.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void Wall::draw(sf::RenderWindow& window, sf::Rect<int> pos)
{
	sf::RectangleShape rect(sf::Vector2f(pos.width, pos.height));
	rect.setPosition(pos.left, pos.top);

	rect.setFillColor(sf::Color::White);

	window.draw(rect);
}
