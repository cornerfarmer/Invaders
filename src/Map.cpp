#include "Map.hpp"
#include "Wall.hpp"
#include "Floor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map()
{
	width = 20;
	height = 20;

	tiles.resize(width);

	for (int x = 0; x < width; x++)
	{
		tiles[x].resize(height);

		for (int y = 0; y < height; y++)
		{
			if (y == 0 || y == height - 1)
				tiles[x][y].reset(new Wall(this));
			else
				tiles[x][y].reset(new Floor(this));
		}
	}
}

void Map::draw(sf::RenderWindow& window)
{
	tileSize = sf::Vector2f(window.getSize().x / width, window.getSize().y / height);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			tiles[x][y]->draw(window, tileSize, sf::Vector2i(x, y));
		}
	}
}

bool Map::isTileWalkable(sf::Vector2i pos) const
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= width || pos.y >= height)
		return false;
	return tiles[pos.x][pos.y]->isWalkable();
}

const sf::Vector2f& Map::getTileSize() const
{
	return tileSize;
}

void Map::doSimulationStep()
{
	time++;
}

void Map::reset()
{
	time = 0;
}

int Map::getTime()
{
	return time;
}