#include "Map.hpp"
#include "Wall.hpp"
#include "Floor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map()
	: player(this, 10, 10)
{
	int width = 20;
	int height = 20;

	tiles.resize(width);

	for (int x = 0; x < width; x++)
	{
		tiles[x].resize(height);

		for (int y = 0; y < height; y++)
		{
			if (y == 0 || y == height - 1)
				tiles[x][y].reset(new Wall());
			else
				tiles[x][y].reset(new Floor());
		}
	}
}

void Map::draw(sf::RenderWindow& window)
{
	int tileSizeX = window.getSize().x / tiles.size();
	int tileSizeY = window.getSize().y / tiles.size();
	for (int x = 0; x < tiles.size(); x++)
	{
		for (int y = 0; y < tiles[x].size(); y++)
		{
			tiles[x][y]->draw(window, sf::Rect<int>(x * tileSizeX, y * tileSizeY, tileSizeX, tileSizeY));
			if (player.getX() == x && player.getY() == y)
				player.draw(window, sf::Vector2f(tileSizeX, tileSizeY));
		}
	}
}

void Map::processEvent(const sf::Event& event)
{
	player.processEvent(event);
}


