#include "Floor.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Wall.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

void Floor::draw(sf::RenderWindow& window, sf::Rect<int> pos)
{
	sf::RectangleShape rect(sf::Vector2f(pos.width, pos.height));
	rect.setPosition(pos.left, pos.top);

	rect.setFillColor(sf::Color(128, 128, 128));

	window.draw(rect);
}
