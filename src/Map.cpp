#include "Map.hpp"
#include "Wall.hpp"
#include "Floor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Invader.hpp"

Map::Map(int width_, int height_)
{
	width = width_;
	height = height_;

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

int Map::draw(sf::RenderWindow& window, int offsetY)
{
	tileSize = sf::Vector2f(window.getSize().x / width, window.getSize().x / width);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			tiles[x][y]->draw(window, tileSize, sf::Vector2i(x, y), sf::Vector2i(0, offsetY));
		}
	}
	return tileSize.y * height + offsetY;
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


int Map::getHeight()
{
	return height;
}

int Map::getWidth()
{
	return width;
}
