[TAS#pragma once

#ifndef _ABSTRACTGAMEOBJECT_HPP_
#define _ABSTRACTGAMEOBJECT_HPP_

#include <SFML/System/Vector2.hpp>

class Map;

class AbstractGameObject
{
private:
	sf::Vector2i pos;
protected:
	AbstractGameObject(const sf::Vector2i& pos);
	const sf::Vector2i getPos();
	void setPos(const sf::Vector2i& newPos, const Map& map);
};

#endif