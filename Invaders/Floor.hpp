#pragma once

#ifndef _FLOOR_HPP_
#define _FLOOR_HPP_

#include "AbstractTile.hpp"

class Floor : public AbstractTile
{
public:
	Floor(const Map* map_);
	void draw(sf::RenderWindow& window, const sf::Vector2f& tileSize, const sf::Vector2i& pos) override;
	bool isWalkable() override;
};

#endif