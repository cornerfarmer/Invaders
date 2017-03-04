#include "Game.hpp"
#include "Map.hpp"

Game::Game()
	:player(&map, sf::Vector2i(10, 10))
{

}


void Game::draw(sf::RenderWindow& window)
{
	map.draw(window);
	player.draw(window);
}

void Game::processEvent(const sf::Event& event)
{
	player.processEvent(event);
}
