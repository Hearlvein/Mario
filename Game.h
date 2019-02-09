#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "Map.h"
#include "Entity.h"
#include "Mario.h"


class Game
{
public:
	Game();
	~Game();

	void processEvents(sf::RenderWindow& window);
	void update(const sf::Time& dt);
	void render(sf::RenderTarget& target);

protected:
	sf::Texture m_texture;

	Map m_map;

	// List structure:
	// 		[0]: mario
	// 		else: mobs
	Mario m_mario;
	std::list<Entity*> m_entities;
};
