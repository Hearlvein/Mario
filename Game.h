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

	const sf::VideoMode getWindowSize() const;
	void processEvents(sf::RenderWindow &window);
	void update(float dt, sf::RenderWindow &window);
	void render(sf::RenderTarget &target);

	void moveEntity(Entity& entity, sf::Vector2f movement);
	bool xTranslate(Entity& entity, float xOffset);
	bool yTranslate(Entity& entity, float yOffset);

  private:
	sf::Texture m_texture;
	Map m_map;
	Mario m_mario;

	sf::RectangleShape m_marioCollider;
};
