#include "State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

State::State()
{
	reset();
}

void State::reset()
{
	mode = PLAY;
	round = 0;
	lives = 5;
}

int State::getRound() const
{
	return round;
}

int State::getLives() const
{
	return lives;
}

bool State::isGameOver() const
{
	return lives <= 0;
}

bool State::substractALive()
{
	lives--;
	return isGameOver();
}

void State::setMode(Mode mode_)
{
	mode = mode_;
}

float State::draw(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 0);

	text.setString("Round: " + std::to_string(round) + " Lives: " + std::to_string(lives));
	window.draw(text);
	return text.getLocalBounds().height + text.getLocalBounds().top + 10;
}

Mode State::getMode() const
{
	return mode;
}

void State::nextRound()
{
	round++;
}

