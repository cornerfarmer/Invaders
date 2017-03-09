#pragma once

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include "AbstractDrawable.hpp"
#include "AbstractGameObject.hpp"

namespace sf {
	class RenderWindow;
}

class Map;

class Player : public AbstractDrawable, public AbstractGameObject
{
	Map* map;
protected:
	bool doStep();
public:
	Player(Map* map, sf::Vector2i pos_);
	virtual void draw(sf::RenderWindow& window);
};

#endif