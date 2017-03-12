#pragma once

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include "AbstractDrawable.hpp"
#include "AbstractGameObject.hpp"

namespace sf {
	class RenderWindow;
}

class World;

class Player : public AbstractDrawable, public AbstractGameObject
{
	World* world;
protected:
	bool doStep();
public:
	Player(World* world, sf::Vector2i pos_);
	virtual void draw(sf::RenderWindow& window, sf::Vector2i offset);
};

#endif