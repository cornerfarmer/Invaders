#pragma once

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include <SFML/Window/Event.hpp>
#include "Map.hpp"
#include "Invader.hpp"
#include <LightBulb/Learning/Reinforcement/DQNLearningRule.hpp>
#include "Inspector.hpp"

class Game
{
private:
	Map map;
	Inspector inspector;
	Player player;
	std::vector<std::unique_ptr<Invader>> invaders;
	std::vector<std::unique_ptr<LightBulb::DQNLearningRule>> learningRules;
	std::shared_ptr<LightBulb::TransitionStorage> transitionStorage;
	void reset();
public:
	Game();
	void draw(sf::RenderWindow& window);
	void step();
};

#endif