#include "LearningController.hpp"
#include "Map.hpp"
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <LightBulb/Function/ActivationFunction/RectifierFunction.hpp>
#include <LightBulb/Function/ActivationFunction/IdentityFunction.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <LightBulb/NeuralNetwork/NeuralNetwork.hpp>


LearningController::LearningController(World* world_)
{
	world = world_;

	LightBulb::DQNLearningRuleOptions options;
	options.environment = world;
	options.initialExploration = 0.1;
	options.finalExploration = 0.1;

	LightBulb::FeedForwardNetworkTopologyOptions networkOptions;
	networkOptions.neuronsPerLayerCount.push_back(28);
	networkOptions.neuronsPerLayerCount.push_back(50);
	networkOptions.neuronsPerLayerCount.push_back(50);
	networkOptions.neuronsPerLayerCount.push_back(4);

	networkOptions.descriptionFactory = new LightBulb::DifferentNeuronDescriptionFactory(new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::RectifierFunction()), new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::IdentityFunction()));
	
	transitionStorage.reset(new LightBulb::TransitionStorage());

	for (int i = 0; i < 5; i++)
	{
		invaders.push_back(std::unique_ptr<Invader>(new Invader(world, sf::Vector2i(0, 0), networkOptions)));
		options.individual = invaders.back().get();

		learningRules.push_back(std::unique_ptr<LightBulb::DQNLearningRule>(new LightBulb::DQNLearningRule(options)));
		learningRules.back()->setTransitionStorage(transitionStorage);
		learningRules.back()->initializeTry();
		world->addGameObject(invaders[i].get());
	}

	invaders[0]->setMarked(true);

	reset();
}

void LearningController::reset()
{
	for (int i = 0; i < invaders.size(); i++)
	{
		sf::Vector2i pos;

		do {
			pos = sf::Vector2i(world->getMap().getWidth() - 5, rand() % world->getMap().getHeight());
		} while (!world->isTileWalkable(pos));
		//pos = sf::Vector2i(15, 10);
		invaders[i]->setPos(pos, *world);
		invaders[i]->setDir(RIGHT);
		invaders[i]->setDead(false);
	}
}

void LearningController::newGame()
{
	for (int i = 0; i < invaders.size(); i++)
		learningRules[i]->initializeTry();
}

void LearningController::draw(sf::RenderWindow& window, int offsetY)
{
	for (int i = 0; i < invaders.size(); i++)
		invaders[i]->draw(window, sf::Vector2i(0, offsetY));
}


void LearningController::storeTransitions(bool force)
{
	LightBulb::Scalar<> reward;
	for (int i = 0; i < invaders.size(); i++)
	{
		if (force || invaders[i]->makesMoveInNextStep())
		{
			invaders[i]->getReward(reward);
			transitionStorage->storeTransition(*invaders[i], *world, reward);
		}
	}
}

void LearningController::doLearning()
{
	for (int r = 0; r < 10000; r++)
	{
		learningRules[0]->doSupervisedLearning();
		if (r % 2000 == 0) {
			learningRules[0]->refreshSteadyNetwork();
		}
	}

	for (int i = 1; i < invaders.size(); i++)
		invaders[i]->getNeuralNetwork().getNetworkTopology().copyWeightsFrom(invaders[0]->getNeuralNetwork().getNetworkTopology());
}

std::vector<std::unique_ptr<Invader>>& LearningController::getInvaders()
{
	return invaders;
}

void LearningController::step()
{
	for (int i = 0; i < invaders.size(); i++)
	{
		invaders[i]->step();
	}
}


bool LearningController::hasRoundEnded()
{
	bool allDead = true;
	for (int i = 0; i < invaders.size(); i++)
	{
		if (!invaders[i]->isDead())
		{
			allDead = false;
		}
	}
	return allDead;
}