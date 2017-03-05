#pragma once

#ifndef _INVADER_HPP_
#define _INVADER_HPP_

#include "AbstractDrawable.hpp"
#include "AbstractGameObject.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractDefaultReinforcementIndividual.hpp"

namespace sf {
	class RenderWindow;
}

class Map;

class Invader : public AbstractDrawable, public AbstractGameObject, public LightBulb::AbstractDefaultReinforcementIndividual
{
	Map* map;
	sf::Vector2i lastPos;
protected:
	void interpretNNOutput(LightBulb::Vector<char>& output) override;
public:
	Invader(Map* map, sf::Vector2i pos_, const LightBulb::FeedForwardNetworkTopologyOptions& networkTopologyOptions);
	virtual void draw(sf::RenderWindow& window);
	void getNNInput(LightBulb::Vector<>& input) const override;
	void isTerminalState(LightBulb::Scalar<char>& isTerminalState) const override;
	void getReward(LightBulb::Scalar<>& reward) const override;
};

#endif