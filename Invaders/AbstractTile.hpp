#pragma once

#ifndef _ABSTRACTTILE_HPP_
#define _ABSTRACTTILE_HPP_

#include <SFML/Graphics/Rect.hpp>
#include "AbstractDrawable.hpp"

namespace sf {
	class RenderWindow;
}

class AbstractTile : public AbstractDrawable
{
protected:
	const Map* map;
public:
	virtual ~AbstractTile() = default;
	AbstractTile(const Map* map_);
	virtual void draw(sf::RenderWindow& window, const sf::Vector2f& tileSize, const sf::Vector2i& pos) = 0;
	virtual bool isWalkable() = 0;
};

#endif