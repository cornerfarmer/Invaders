#include "Floor.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Wall.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Floor::Floor(const Map* map_)
	:AbstractTile(map_)
{

}

void Floor::draw(sf::RenderWindow& window, const sf::Vector2f& tileSize, const sf::Vector2i& pos)
{
	drawTile(window, *map, pos, sf::Color(128, 128, 128));
}

bool Floor::isWalkable()
{
	return true;
}
