#include "Game.h"
#include "TileType.h"
#include <iostream>


Game::Game() :
	m_mario(m_texture, sf::IntRect(0, 0, 50, 50), sf::Vector2f(), sf::Vector2f(1.f, 1.f))
{
    m_texture.loadFromFile("texture.png");
    m_map.load("");
	m_entities.push_back(&m_mario);
}

Game::~Game()
{

}

void Game::processEvents(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_mario.fire();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_mario.goLeft();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_mario.goRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_mario.goUp();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_mario.goDown();
}

void Game::update(const sf::Time& dt)
{
	/*for (Entity& entity: m_entities)
		entity.update(dt);*/

    m_map.set(0, 2, Block);
    m_map.set(1, 3, Block);
    m_map.set(2, 4, Block);
    m_map.set(3, 5, Block);
}

void Game::render(sf::RenderTarget& target)
{
	target.clear();

	sf::RenderStates states = sf::RenderStates::Default;
	states.texture = &m_texture;

    m_map.draw(target, states);

	for (const Entity* entity: m_entities)
        target.draw(*entity, states);
}
