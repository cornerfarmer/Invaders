#include "AbstractGameObject.hpp"
#include "Map.hpp"

AbstractGameObject::AbstractGameObject(const sf::Vector2i& pos_)
{
	pos = pos_;
	dead = false;
}

const sf::Vector2i AbstractGameObject::getPos() const
{
	return pos;
}

sf::Vector2i AbstractGameObject::getDirVector() const
{
	return sf::Vector2i(dir == 1 ? 1 : (dir == 3 ? -1 : 0), dir == 2 ? 1 : (dir == 0 ? -1 : 0));
}

void AbstractGameObject::setPos(const sf::Vector2i& newPos, const Map& map)
{
	if (newPos != pos && map.isTileWalkable(newPos))
		pos = newPos;
}

void AbstractGameObject::walk(const Map& map, Direction newDir, int distance)
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
	setPos(nextPos, map);
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
