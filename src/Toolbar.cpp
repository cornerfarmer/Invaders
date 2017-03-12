#include "Toolbar.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.hpp"
#include <SFML/Graphics/Text.hpp>

Toolbar::Toolbar(Game* game_)
{
	game = game_;
}

void Toolbar::draw(sf::RenderWindow& window, sf::Vector2i offset)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::White);
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(sf::Vector2f(10, offset.y + 10));
	playRect = rect.getGlobalBounds();

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
		
	window.draw(rect);
	text.setPosition(playRect.left + playRect.width / 2, playRect.top + playRect.height / 2);
	text.setString(">");
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	window.draw(text);

	rect.move(60, 0);
	pauseRect = rect.getGlobalBounds();
	window.draw(rect);
	text.setPosition(pauseRect.left + pauseRect.width / 2, pauseRect.top + pauseRect.height / 2);
	text.setString("||");
	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	window.draw(text);

	rect.move(60, 0);
	nextRect = rect.getGlobalBounds();
	window.draw(rect);
	text.setPosition(nextRect.left + nextRect.width / 2, nextRect.top + nextRect.height / 2);
	text.setString(">|");
	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	window.draw(text);
}

void Toolbar::click(const sf::Event::MouseButtonEvent& event)
{
	if (playRect.contains(event.x, event.y))
		game->play();
	else if (pauseRect.contains(event.x, event.y))
		game->pause();
	else if (nextRect.contains(event.x, event.y))
		game->nextStep();
}
