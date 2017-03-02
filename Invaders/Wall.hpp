#pragma once

#ifndef _WALL_HPP_
#define _WALL_HPP_

#include "AbstractTile.hpp"

class Wall : public AbstractTile
{
public:
	void draw(sf::RenderWindow& window, sf::Rect<int> pos) override;
};

#endif