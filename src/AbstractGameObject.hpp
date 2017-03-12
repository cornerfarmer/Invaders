#pragma once

#ifndef _ABSTRACTGAMEOBJECT_HPP_
#define _ABSTRACTGAMEOBJECT_HPP_

#include <SFML/System/Vector2.hpp>

class World;

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
	int ticksSinceLastStep;
	int speed;
	bool madeMove;
protected:
	Direction dir;
	bool dead;
	AbstractGameObject(const sf::Vector2i& pos, int speed_);
	void walk(const World& world, Direction dir, int distance = 1);
	virtual bool doStep() = 0;
public:
	virtual ~AbstractGameObject() {};
	void setDir(const Direction& dir);
	void setDead(bool dead_);
	bool isDead();
	void setPos(const sf::Vector2i& newPos, const World& world);
	const sf::Vector2i getPos() const;
	sf::Vector2i getDirVector() const;
	void step();
	bool madeMoveInLastStep();
};

#endif 