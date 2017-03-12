#include "Game.hpp"
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


Game::Game()
	: toolbar(this), learningController(&world)
{
	inspector.select(learningController.getInvaders()[0].get());
	learningController.getInvaders()[0]->setMarked(true);

	reset();
}

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
		learningController.step();

		world.doSimulationStep();
		
		world.checkIndividualPositions(state);

		learningController.storeTransitions();

		if (learningController.hasRoundEnded())
		{
			reset();
			learningController.doLearning();
			state.nextRound();
		}

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
