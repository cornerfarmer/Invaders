#include "Game.hpp"
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <LightBulb/Learning/AbstractLearningResult.hpp>
#include <LightBulb/Learning/LearningState.hpp>

Game::Game()
	: toolbar(this), learningController(&world)
{
	inspector.select(learningController.getInvaders()[0].get());
	learningController.getInvaders()[0]->setMarked(true);

	reset();
}

Game::~Game() = default;

void Game::reset()
{
	world.reset();
	learningController.reset();
}

void Game::newGame()
{
	reset();
	learningController.newGame();
	state.reset();
}

void Game::draw(sf::RenderWindow& window)
{
	int offsetY = state.draw(window);
	int offsetYAfterMap = world.draw(window, offsetY);
	learningController.draw(window, offsetY);
	inspector.draw(window, sf::Vector2i(window.getSize().x / 2, offsetYAfterMap));
	toolbar.draw(window, sf::Vector2i(0, offsetYAfterMap));
}


void Game::click(sf::Event::MouseButtonEvent event)
{
	toolbar.click(event);
}

void Game::step()
{
	if (state.getMode() == PLAY || state.getMode() == ONESTEP)
	{
		if (world.getTime() != 0)
			learningController.storeTransitions(learningController.hasRoundEnded());

		if (learningController.hasRoundEnded())
		{
			reset();
			learningController.doLearning();
			state.nextRound();
			return;
		}

		learningController.step();

		world.doSimulationStep();
		
		if (world.checkIndividualPositions(state))	
			newGame();

		if (state.getMode() == ONESTEP)
			state.setMode(PAUSE);
	}
}


void Game::play()
{
	state.setMode(PLAY);
}

void Game::pause()
{
	state.setMode(PAUSE);
}

void Game::nextStep()
{
	state.setMode(ONESTEP);
}


void Game::run(bool initial)
{
	if (initial)
	{
		learningRule.reset(createLearningRate());
		//learningResult.reset(learningRule->start());
	}
	else
	{
		//learningResult.reset(learningRule->resume());
	}

	learningRule->initializeBeforeStart();
	getLearningState().addTry();

	while(isRunning())
	{
		step();
		getLearningState().iterations++;
	}

	if (isPausing())
		pausingFinished();
	else
		finished();
}



std::string Game::getOriginalName() const
{
	return "Game";
}

std::string Game::getDescription() const
{
	return "A game!";
}


LightBulb::AbstractTrainingPlan* Game::createNewFromSameType() const
{
	return new Game();
}


std::string Game::getLearningRuleName() const
{
	return LightBulb::DQNLearningRule::getName();
}

LightBulb::AbstractLearningRule* Game::createLearningRate()
{
	return learningController.createLearningRule();
}
