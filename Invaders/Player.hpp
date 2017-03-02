#pragma once

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

namespace sf {
	class RenderWindow;
}

class Map;

class Player
{
	int posX;
	int posY;
	Map* map;
public:
	Player(Map* map, int posX_, int posY_);
	virtual void draw(sf::RenderWindow& window, sf::Vector2f tileSize);
	int getX();
	int getY();
	void processEvent(const sf::Event& event);
};

#endif