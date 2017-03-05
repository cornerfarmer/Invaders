#pragma once

#ifndef _ABSTRACTGAMEOBJECT_HPP_
#define _ABSTRACTGAMEOBJECT_HPP_

#include <SFML/System/Vector2.hpp>

class Map;

enum Direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

class AbstractGameObject
{
private:
	sf::Vector2i pos;
protected:
	Direction dir;
	AbstractGameObject(const sf::Vector2i& pos);
	const sf::Vector2i getPos();
	void setPos(const sf::Vector2i& newPos, const Map& map);
};

#endif 