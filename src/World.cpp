#include "World.hpp"
#include "Map.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "State.hpp"


World::World()
	:player(this, sf::Vector2i(10, 10)), map(50, 10)
{
	addGameObject(&player);

	reset();
}

void World::reset()
{
	time = 0;
	player.setPos(sf::Vector2i(5, map.getHeight() / 2), *this);
}

int World::draw(sf::RenderWindow& window, int offsetY)
{
	int offsetYAfterMap = map.draw(window, offsetY);
	player.draw(window, sf::Vector2i(0, offsetY));
	return offsetYAfterMap;
}

bool World::checkIndividualPositions(State& state)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isDead() && gameObjects[i] != &player)
		{
			if (abs((gameObjects[i]->getPos() - player.getPos()).x) + abs((gameObjects[i]->getPos() - player.getPos()).y) <= 1)
				gameObjects[i]->setDead(true);
			else if (gameObjects[i]->getPos().x == 0)
			{
				gameObjects[i]->setDead(true);
				if (state.substractALive())
				{
					return true;
				}
			}
		}
	}
	return false;
}

void World::doSimulationStep()
{
	time++;

	player.step();
}

int World::getTime()
{
	return time;
}

void World::addGameObject(AbstractGameObject* newGameObject)
{
	gameObjects.push_back(newGameObject);
}

bool World::isTileWalkable(sf::Vector2i pos) const
{
	for (auto gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
	{
		if ((*gameObject)->getPos() == pos && !(*gameObject)->isDead())
			return false;
	}
	return map.isTileWalkable(pos);
}

float World::getTileValue(sf::Vector2i pos) const
{
	if (isTileWalkable(pos))
	{
		return 1;
	}
	else
	{
		for (auto gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
		{
			if ((*gameObject)->getPos() == pos && !(*gameObject)->isDead())
			{
				if (dynamic_cast<Player*>(*gameObject))
					return 0;
				else if (dynamic_cast<Invader*>(*gameObject))
					return 1;
			}
		}
		return 1;
	}
}

Map& World::getMap()
{
	return map;
}
