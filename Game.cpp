#include "Game.h"
#include "TileType.h"
#include <iostream>

Game::Game() : m_mario()
{
	m_texture.loadFromFile("texture.png");
	m_map.load("");

	m_map.set(0, 2, Block);
	m_map.set(1, 3, Block);
	m_map.set(2, 4, Block);
	m_map.set(3, 5, Block);
}

Game::~Game()
{
}

const sf::VideoMode Game::getWindowSize() const
{
	return sf::VideoMode(m_map.getWidth() * m_map.getTileSize(), m_map.getHeight() * m_map.getTileSize());
}

void Game::processEvents(sf::RenderWindow &window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
                m_mario.beginMotion(sf::Vector2f(-1.f, 0.f));

            /* else if (event.key.code == sf::Keyboard::Right)
                m_mario.beginMotion(sf::Vector2f(1.f, 0.f)); */
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                m_mario.endMotion();
        }
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_mario.beginMotion(sf::Vector2f(1.f, 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_mario.fire();
}

void Game::update(float dt, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        m_mario.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

	m_mario.update(dt);

	moveEntity(m_mario, m_mario.getMovementVector());
}

void Game::render(sf::RenderTarget &target)
{
	target.clear();

	sf::RenderStates states = sf::RenderStates::Default;
	states.texture = &m_texture;

	m_map.draw(target, states);
	target.draw(m_marioCollider);
	target.draw(m_mario);
}

void Game::moveEntity(Entity& entity, sf::Vector2f movement)
{
	xTranslate(entity, movement.x);
	yTranslate(entity, movement.y);
}

bool Game::xTranslate(Entity& entity, float xOffset)
{
	int xmin = std::floor((entity.getPosition().x + xOffset) / m_map.getTileSize());
	int xmax = std::floor((entity.getPosition().x + entity.getLocalBounds().width - 1 + xOffset) / m_map.getTileSize());
	int ymin = std::floor(entity.getPosition().y / m_map.getTileSize());
	int ymax = std::floor((entity.getPosition().y + entity.getLocalBounds().height - 1) / m_map.getTileSize());

	if (xmin > 0 && xmax < (int)m_map.getWidth())
	{
		for (int i = xmin; i <= xmax; ++i)
			for (int j = ymin; j <= ymax; ++j)
				if (m_map.at(i, j) != Void)
					return false;

		entity.move(xOffset, 0.f);
		return true;
	}

	return false;
}
bool Game::yTranslate(Entity &entity, float yOffset)
{
	int xmin = std::floor((entity.getPosition().x) / m_map.getTileSize());
	int xmax = std::floor((entity.getPosition().x + entity.getLocalBounds().width - 1) / m_map.getTileSize());
	int ymin = std::floor((entity.getPosition().y + yOffset) / m_map.getTileSize());
	int ymax = std::floor((entity.getPosition().y + entity.getLocalBounds().height - 1 + yOffset) / m_map.getTileSize());

	if (ymin > 0 && ymax < (int)m_map.getHeight())
	{
		for (int i = xmin; i <= xmax; ++i)
			for (int j = ymin; j <= ymax; ++j)
				if (m_map.at(i, j) != Void)
					return false;

		entity.move(0.f, yOffset);
		return true;
	}

	return false;
}
