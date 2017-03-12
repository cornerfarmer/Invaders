#pragma once

#ifndef _ABSTRACTDRAWABLE_HPP_
#define _ABSTRACTDRAWABLE_HPP_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

class Map;

namespace sf {
	class RenderWindow;
}

class AbstractDrawable
{
protected:
	static sf::Font font;
	void drawTile(sf::RenderWindow& window, const Map& map, const sf::Vector2i& pos, const sf::Color& color, const sf::Vector2i& offset);
public:
	AbstractDrawable();
};

#endif