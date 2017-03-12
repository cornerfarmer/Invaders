#pragma once

#ifndef _STATE_HPP_
#define _STATE_HPP_

#include "AbstractDrawable.hpp"

enum Mode
{
	PLAY,
	PAUSE,
	ONESTEP
};

class State : public virtual AbstractDrawable
{
private:
	Mode mode;
	int round;
	int lives;
public:
	State();
	void reset();
	void nextRound();
	Mode getMode() const;
	int getRound() const;
	int getLives() const;
	bool isGameOver() const;
	bool substractALive();
	void setMode(Mode mode_);
	float draw(sf::RenderWindow& window);
};

#endif