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

enum Direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

class Player : public AbstractDrawable, public AbstractGameObject
{
	Direction dir;
	Map* map;
public:
	Player(Map* map, sf::Vector2i pos_);
	virtual void draw(sf::RenderWindow& window);
	void processEvent(const sf::Event& event);
};

#endif