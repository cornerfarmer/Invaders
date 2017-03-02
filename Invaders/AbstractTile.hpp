#pragma once

#ifndef _ABSTRACTTILE_HPP_
#define _ABSTRACTTILE_HPP_

#include <SFML/Graphics/Rect.hpp>

namespace sf {
	class RenderWindow;
}

class AbstractTile
{
public:
	virtual ~AbstractTile() = default;
	virtual void draw(sf::RenderWindow& window, sf::Rect<int> pos) = 0;
};

#endif