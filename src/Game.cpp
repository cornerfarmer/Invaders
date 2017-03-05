#include "Game.hpp"
#include "Map.hpp"
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <LightBulb/Function/ActivationFunction/RectifierFunction.hpp>
#include <LightBulb/Function/ActivationFunction/IdentityFunction.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>


Game::Game()
	:player(&map, sf::Vector2i(10, 10))
{
	LightBulb::DQNLearningRuleOptions options;
	options.environment = &map;
	options.initialExploration = 0.1;
	options.finalExploration = 0.1;

	LightBulb::FeedForwardNetworkTopologyOptions networkOptions;
	networkOptions.neuronsPerLayerCount.push_back(11);
	networkOptions.neuronsPerLayerCount.push_back(20);
	networkOptions.neuronsPerLayerCount.push_back(4);

	networkOptions.descriptionFactory = new LightBulb::DifferentNeuronDescriptionFactory(new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::RectifierFunction()), new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::IdentityFunction()));
	
	transitionStorage.reset(new LightBulb::TransitionStorage());

	for (int i = 0; i < 1; i++)
	{
		invaders.push_back(std::unique_ptr<Invader>(new Invader(&map, sf::Vector2i(15, 10), networkOptions)));
		options.individual = invaders.back().get();

		learningRules.push_back(std::unique_ptr<LightBulb::DQNLearningRule>(new LightBulb::DQNLearningRule(options)));
		learningRules.back()->setTransitionStorage(transitionStorage);
		learningRules.back()->initializeTry();
	}

}

void Game::reset()
{
	map.reset();
	for (int i = 0; i < 1; i++)
	{
		invaders[i]->setPos(sf::Vector2i(15, 10), map);
		invaders[i]->setDir(RIGHT);
	}
}

void Game::draw(sf::RenderWindow& window)
{
	map.draw(window);
	player.draw(window);
	for (int i = 0; i < 1; i++)
		invaders[i]->draw(window);
}

void Game::processEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		for (int i = 0; i < 1; i++)
			invaders[i]->doSimulationStep();

		map.doSimulationStep();

		player.processEvent(event);

		LightBulb::Scalar<> reward;
		for (int i = 0; i < 1; i++) {
			invaders[i]->getReward(reward);
			transitionStorage->storeTransition(*invaders[i], map, reward);
		}

		if (map.getTime() >= 10)
		{
			reset();
			for (int r = 0; r < 100; r++) 
			{
				for (int i = 0; i < 1; i++)
					learningRules[i]->doSupervisedLearning();
			}
			for (int i = 0; i < 1; i++)
				learningRules[i]->refreshSteadyNetwork();
		}
	}
}
