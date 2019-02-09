#include "Game.h"


Game::Game() :
	m_mario(m_texture, sf::IntRect(0, 0, 50, 50), sf::Vector2f(), sf::Vector2f(1.f, 1.f))
{
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
}

void Game::update(const sf::Time& dt)
{
	/*for (Entity& entity: m_entities)
		entity.update(dt);*/
}

void Game::render(sf::RenderTarget& target) const
{
	target.clear();

	for (const Entity* entity: m_entities)
		target.draw(*entity, sf::RenderStates::Default);
}
