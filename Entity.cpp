#include "Entity.h"
#include <iostream>

const float Entity::GRAVITY = 100.f;

Entity::Entity()
{
	m_movement = sf::Vector2f(0.f, GRAVITY);
}

Entity::~Entity()
{
}

void Entity::update(float dt)
{
	std::cout << "Motion state: " << m_motionState << std::endl;

	if (m_motionState == Begin && m_motionDuration.getElapsedTime().asSeconds() >= m_middleMotionState)
		m_motionState = Middle;
	else if (m_motionState == End && m_motionDuration.getElapsedTime().asSeconds() >= m_finalMotionEnd)
	{
		m_motionState = None;
		m_movement = sf::Vector2f(0.f, GRAVITY);
	}

	if (m_motionState != None)
	{
		if (m_direction.x != 0.f)
		{
			float x = 0.f;

			if (m_motionState == Begin)
				x = m_motionDuration.getElapsedTime().asSeconds() / m_middleMotionState * m_xvel * dt;
			else if (m_motionState == Middle)
				x = m_xvel * dt;
			else if (m_motionState == End)
				x = (1 - m_motionDuration.getElapsedTime().asSeconds() / m_middleMotionState) * m_xvel * dt;

			m_movement.x = (m_direction.x == 1) ? x : -x;
		}
	}

	m_movement.y = GRAVITY * dt;
}

sf::Vector2f& Entity::getMovementVector()
{
	return m_movement;
}

void Entity::beginMotion(sf::Vector2f dir)
{
	if (dir != sf::Vector2f(0.f, 0.f) && (m_motionState == None || m_motionState == End))
	{
		m_motionState = Begin;
		m_direction = dir;
		m_motionDuration.restart();
	}
}

void Entity::endMotion()
{
	if (m_motionState == Begin || m_motionState == Middle)
	{
		m_motionState = End;
		m_motionDuration.restart();
	}
}
