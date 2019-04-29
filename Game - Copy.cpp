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
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_mario.fire();

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	// 	m_mario.goLeft();
	// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	// 	m_mario.goRight();

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	// 	m_mario.goUp();
	// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	// 	m_mario.goDown();
}

void Game::update()
{
	// std::cout << "actual mario position: " << m_mario.getPosition().x << ";" << m_mario.getPosition().y << std::endl;

	sf::Vector2f marioVel(-2, 1.3);
	sf::Vector2f marioNewTopLeft = m_mario.getPosition() + marioVel;
	sf::Vector2f marioNewBottomRight = marioNewTopLeft + sf::Vector2f(m_mario.getLocalBounds().width, m_mario.getLocalBounds().height);

	// std::cout << "go to mario top position: " << marioNewTopLeft.x << ";" << marioNewTopLeft.y << std::endl;
	// std::cout << "go to mario bot position: " << marioNewBottomRight.x << ";" << marioNewBottomRight.y << std::endl;

	int xa = std::floor(marioNewTopLeft.x		/ m_map.getTileSize());
	int ya = std::floor(marioNewTopLeft.y 		/ m_map.getTileSize());
	int xb = std::floor(marioNewBottomRight.x	/ m_map.getTileSize());
	int yb = std::floor(marioNewBottomRight.y	/ m_map.getTileSize());
	if ((int)marioNewBottomRight.x % (int)m_map.getTileSize() == 0) xb--;
	if ((int)marioNewBottomRight.y % (int)m_map.getTileSize() == 0) yb--;
	/*std::cout << "xa: " << xa << std::endl;
	std::cout << "ya: " << ya << std::endl;
	std::cout << "xb: " << xb << std::endl;
	std::cout << "yb: " << yb << std::endl;*/

	bool canMove = true;

	if (xa < 0 || ya < 0 || xb >= (int)m_map.getWidth() || yb >= (int)m_map.getHeight())
	{
		// std::cout << "out of grid" << std::endl;
		canMove = false;
	}

	if (canMove)
		for (int i = xa; i <= xb; ++i)
			for (int j = ya; j <= yb; ++j)
				if (m_map.at(i, j) != Void)
					canMove = false;

	if (canMove)
		m_mario.setPosition(marioNewTopLeft);
}

void Game::moveEntity(Entity& entity, sf::Vector2f& velocity)
{
	int xmin = (entity.getPosition().x + velocity.x) / m_map.getTileSize();
	int xmax = (entity.getPosition().x + entity.getLocalBounds().width - 1 + velocity.x) / m_map.getTileSize();
	int ymin = (entity.getPosition().y + velocity.y) / m_map.getTileSize();
	int ymax = (entity.getPosition().y + entity.getLocalBounds().height - 1 + velocity.y) / m_map.getTileSize();

	// X-translation

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
