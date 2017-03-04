#pragma once

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include <SFML/Window/Event.hpp>
#include "Map.hpp"

class Game
{
private:
	Map map;
	Player player;
public:
	Game();
	void draw(sf::RenderWindow& window);
	void processEvent(const sf::Event& event);
};

#endif