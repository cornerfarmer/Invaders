#pragma once

#ifndef _INSPECTOR_HPP_
#define _INSPECTOR_HPP_

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "AbstractDrawable.hpp"

namespace sf {
	class RenderWindow;
}

class Invader;

class Inspector : public virtual AbstractDrawable
{
private:
	Invader* selected;
	std::string renderFloat(float number);
public:
	Inspector();
	void select(Invader* invader);
	void draw(sf::RenderWindow& window, sf::Vector2i offset);
};

#endif