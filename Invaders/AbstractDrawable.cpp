#include "AbstractDrawable.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp"

void AbstractDrawable::drawTile(sf::RenderWindow& window, const Map& map, const sf::Vector2i& pos, const sf::Color& color)
{
	sf::RectangleShape rect(map.getTileSize());
	rect.setPosition(map.getTileSize().x * pos.x, map.getTileSize().y * pos.y);
	rect.setFillColor(color);
	window.draw(rect);
}
