#include "Game.hpp"
#include "Map.hpp"
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <LightBulb/Function/ActivationFunction/FermiFunction.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>

Game::Game()
	:player(&map, sf::Vector2i(10, 10))
{
	LightBulb::DQNLearningRuleOptions options;
	options.environment = &map;

	LightBulb::FeedForwardNetworkTopologyOptions networkOptions;
	networkOptions.neuronsPerLayerCount.push_back(10);
	networkOptions.neuronsPerLayerCount.push_back(5);
	networkOptions.neuronsPerLayerCount.push_back(2);

	networkOptions.descriptionFactory = new LightBulb::SameNeuronDescriptionFactory(new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::FermiFunction));
	
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
	}
}
