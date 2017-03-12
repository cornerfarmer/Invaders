#include "AbstractGameObject.hpp"
#include "Map.hpp"
#include "World.hpp"

AbstractGameObject::AbstractGameObject(const sf::Vector2i& pos_, int speed_)
{
	pos = pos_;
	dead = false;
	speed = speed_;
	ticksSinceLastStep = speed;
	madeMove = false;
}

const sf::Vector2i AbstractGameObject::getPos() const
{
	return pos;
}

sf::Vector2i AbstractGameObject::getDirVector() const
{
	return sf::Vector2i(dir == 1 ? 1 : (dir == 3 ? -1 : 0), dir == 2 ? 1 : (dir == 0 ? -1 : 0));
}

void AbstractGameObject::step()
{
	madeMove = false;
	if (ticksSinceLastStep-- <= 0)
	{
		bool stepExecuted = doStep();
		if (stepExecuted) {
			ticksSinceLastStep = speed;
			madeMove = true;
		}
	}
}

bool AbstractGameObject::madeMoveInLastStep()
{
	return madeMove;
}

void AbstractGameObject::setPos(const sf::Vector2i& newPos, const World& world)
{
	if (newPos != pos && world.isTileWalkable(newPos))
		pos = newPos;
}

void AbstractGameObject::walk(const World& world, Direction newDir, int distance)
{
	sf::Vector2i nextPos = getPos();
	if (newDir == LEFT)
	{
		nextPos.x -= distance;
	}
	else if (newDir == RIGHT)
	{
		nextPos.x += distance;
	}
	else if (newDir == UP)
	{
		nextPos.y -= distance;
	}
	else if (newDir == DOWN)
	{
		nextPos.y += distance;
	}
	dir = newDir;
	setPos(nextPos, world);
}

void AbstractGameObject::setDir(const Direction& dir_)
{
	dir = dir_;
}


void AbstractGameObject::setDead(bool dead_)
{
	dead = dead_;
}

bool AbstractGameObject::isDead()
{
	return dead;
}
