#include "AbstractDrawable.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.hpp"

sf::Font AbstractDrawable::font = sf::Font();

AbstractDrawable::AbstractDrawable()
{
	if (font.getInfo().family == "")
		font.loadFromFile("segoeui.ttf");
}

void AbstractDrawable::drawTile(sf::RenderWindow& window, const Map& map, const sf::Vector2i& pos, const sf::Color& color, const sf::Vector2i& offset)
{
	sf::RectangleShape rect(map.getTileSize());
	rect.setPosition(map.getTileSize().x * pos.x + offset.x, map.getTileSize().y * pos.y + offset.y);
	rect.setFillColor(color);
	window.draw(rect);
}
