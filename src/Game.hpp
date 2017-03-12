#pragma once

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Window/Event.hpp>
#include "Invader.hpp"
#include <LightBulb/Learning/Reinforcement/DQNLearningRule.hpp>
#include "Inspector.hpp"
#include "Toolbar.hpp"
#include "State.hpp"
#include "World.hpp"
#include "LearningController.hpp"

class Game
{
private:
	State state;
	World world;
	Inspector inspector;
	Toolbar toolbar;
	LearningController learningController;
	void reset();
	void newGame();
public:
	Game();
	void draw(sf::RenderWindow& window);
	void step();
	void click(sf::Event::MouseButtonEvent event);
	void play();
	void pause();
	void nextStep();
};

#endif