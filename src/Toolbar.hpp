#pragma once

#ifndef _TOOLBAR_HPP_
#define _TOOLBAR_HPP_

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "AbstractDrawable.hpp"

namespace sf {
	class RenderWindow;
}

class Game;

class Toolbar : public virtual AbstractDrawable
{
private:
	Game* game;
	sf::FloatRect playRect;
	sf::FloatRect pauseRect;
	sf::FloatRect nextRect;
public:
	Toolbar(Game* game_);
	void draw(sf::RenderWindow& window, sf::Vector2i offset);
	void click(const sf::Event::MouseButtonEvent& event);
};

#endif