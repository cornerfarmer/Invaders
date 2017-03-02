#pragma once

#ifndef _FLOOR_HPP_
#define _FLOOR_HPP_

#include "AbstractTile.hpp"

class Floor : public AbstractTile
{
public:
	void draw(sf::RenderWindow& window, sf::Rect<int> pos) override;
};

#endif