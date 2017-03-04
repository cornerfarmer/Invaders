#pragma once

#ifndef _ABSTRACTDRAWABLE_HPP_
#define _ABSTRACTDRAWABLE_HPP_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

class Map;

namespace sf {
	class RenderWindow;
}

class AbstractDrawable
{
protected:
	void drawTile(sf::RenderWindow& window, const Map& map, const sf::Vector2i& pos, const sf::Color& color);
};

#endif