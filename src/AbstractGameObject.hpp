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
	bool dead;
	AbstractGameObject(const sf::Vector2i& pos);
	void walk(const Map& map, Direction dir, int distance = 1);
public:
	void setDir(const Direction& dir);
	void setDead(bool dead_);
	bool isDead();
	void setPos(const sf::Vector2i& newPos, const Map& map);
	const sf::Vector2i getPos() const;
	sf::Vector2i getDirVector() const;
};

#endif 