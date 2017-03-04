#include "AbstractGameObject.hpp"
#include "Map.hpp"

AbstractGameObject::AbstractGameObject(const sf::Vector2i& pos_)
{
	pos = pos_;
}

const sf::Vector2i AbstractGameObject::getPos()
{
	return pos;
}

void AbstractGameObject::setPos(const sf::Vector2i& newPos, const Map& map)
{
	if (newPos != pos && map.isTileWalkable(newPos))
		pos = newPos;
}
