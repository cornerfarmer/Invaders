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
#include "LightBulbApp/TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"

class Game : public LightBulb::AbstractLearningRuleTrainingPlan
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
	~Game();
	void draw(sf::RenderWindow& window);
	void step();
	void click(sf::Event::MouseButtonEvent event);
	void play();
	void pause();
	void nextStep();
	void run(bool initial);
protected:
	AbstractTrainingPlan* createNewFromSameType() const override;
public:
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	std::string getLearningRuleName() const override;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
};

#endif