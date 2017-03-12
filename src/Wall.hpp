#pragma once

#ifndef _WALL_HPP_
#define _WALL_HPP_

#include "AbstractTile.hpp"

class Wall : public AbstractTile
{
public:
	Wall(const Map* map_);
	void draw(sf::RenderWindow& window, const sf::Vector2f& tileSize, const sf::Vector2i& pos, const sf::Vector2i& offset) override;
	bool isWalkable() override;
};

#endif