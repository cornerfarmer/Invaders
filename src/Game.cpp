#include "Game.hpp"
#include "Map.hpp"
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <LightBulb/Function/ActivationFunction/RectifierFunction.hpp>
#include <LightBulb/Function/ActivationFunction/IdentityFunction.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>


Game::Game()
	:player(&map, sf::Vector2i(10, 10)), map(50, 10)
{
	map.addGameObject(&player);

	LightBulb::DQNLearningRuleOptions options;
	options.environment = &map;
	options.initialExploration = 0.1;
	options.finalExploration = 0.1;

	LightBulb::FeedForwardNetworkTopologyOptions networkOptions;
	networkOptions.neuronsPerLayerCount.push_back(27);
	networkOptions.neuronsPerLayerCount.push_back(40);
	networkOptions.neuronsPerLayerCount.push_back(4);

	networkOptions.descriptionFactory = new LightBulb::DifferentNeuronDescriptionFactory(new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::RectifierFunction()), new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::IdentityFunction()));
	
	transitionStorage.reset(new LightBulb::TransitionStorage());

	for (int i = 0; i < 5; i++)
	{
		invaders.push_back(std::unique_ptr<Invader>(new Invader(&map, sf::Vector2i(0, 0), networkOptions)));
		options.individual = invaders.back().get();

		learningRules.push_back(std::unique_ptr<LightBulb::DQNLearningRule>(new LightBulb::DQNLearningRule(options)));
		learningRules.back()->setTransitionStorage(transitionStorage);
		learningRules.back()->initializeTry();
		map.addGameObject(invaders[i].get());
	}

	reset();
}

void Game::reset()
{
	map.reset();
	player.setPos(sf::Vector2i(5, map.getHeight() / 2), map);
	for (int i = 0; i < invaders.size(); i++)
	{
		sf::Vector2i pos;

		do {
			pos = sf::Vector2i(map.getWidth() - 5, rand() % map.getHeight());
		} while (!map.isTileWalkable(pos));
		//pos = sf::Vector2i(15, 10);
		invaders[i]->setPos(pos, map);
		invaders[i]->setDir(RIGHT);
		invaders[i]->setDead(false);
	}
}

void Game::draw(sf::RenderWindow& window)
{
	map.draw(window);
	player.draw(window);
	for (int i = 0; i < invaders.size(); i++)
		invaders[i]->draw(window);
}

void Game::step()
{
	for (int i = 0; i < invaders.size(); i++)
	{
		if (!invaders[i]->isDead())
			invaders[i]->doSimulationStep();
	}

	map.doSimulationStep();

	player.step();

	LightBulb::Scalar<> reward;
	bool allDead = true;
	for (int i = 0; i < invaders.size(); i++) 
	{
		if (!invaders[i]->isDead())
		{
			if (abs((invaders[i]->getPos() - player.getPos()).x) + abs((invaders[i]->getPos() - player.getPos()).y) <= 1 || invaders[i]->getPos().x == 0)
				invaders[i]->setDead(true);
			invaders[i]->getReward(reward);
			transitionStorage->storeTransition(*invaders[i], map, reward);
			allDead = false;
		}
	}

	if (allDead)
	{
		reset();
		for (int r = 0; r < 10000; r++) 
		{
			for (int i = 0; i < invaders.size(); i++)
				learningRules[i]->doSupervisedLearning();
		}
		for (int i = 0; i < invaders.size(); i++)
			learningRules[i]->refreshSteadyNetwork();
	}
}
