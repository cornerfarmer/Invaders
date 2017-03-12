#pragma once

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "Player.hpp"
#include <SFML/Window/Event.hpp>
#include "Map.hpp"
#include "Invader.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"

class State;

class World : public LightBulb::AbstractReinforcementEnvironment
{
private:
	Map map;
	Player player;
	int time;
	std::vector<AbstractGameObject*> gameObjects;
public:
	World();
	int draw(sf::RenderWindow& window, int offsetY);
	bool checkIndividualPositions(State& state);
	void doSimulationStep() override;
	void reset();
	int getTime();
	void addGameObject(AbstractGameObject* newGameObject);
	bool isTileWalkable(sf::Vector2i pos) const;
	float getTileValue(sf::Vector2i pos) const;
	Map& getMap();
};

#endif