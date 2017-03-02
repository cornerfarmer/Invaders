#pragma once

#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <vector>
#include <memory>
#include "AbstractTile.hpp"
#include "Player.hpp"
#include <SFML/Window/Event.hpp>

class Map
{
private:
	std::vector<std::vector<std::unique_ptr<AbstractTile>>> tiles;
	Player player;
public:
	Map();
	void draw(sf::RenderWindow& window);
	void processEvent(const sf::Event& event);
};

#endif