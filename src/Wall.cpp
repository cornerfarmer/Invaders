#include "Wall.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Wall::Wall(const Map* map_)
	:AbstractTile(map_)
{

}

void Wall::draw(sf::RenderWindow& window, const sf::Vector2f& tileSize, const sf::Vector2i& pos, const sf::Vector2i& offset)
{
	drawTile(window, *map, pos, sf::Color::White, offset);
}

bool Wall::isWalkable()
{
	return false;
}
