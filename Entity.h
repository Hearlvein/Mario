#pragma once

#include <SFML/Graphics.hpp>

enum MotionState { None, Begin, Middle, End };

class Entity : public sf::Sprite
{
public:
	Entity();
	~Entity();

	void update(float dt);

	sf::Vector2f& getMovementVector();
	void beginMotion(sf::Vector2f dir);
	void endMotion();

	static const float GRAVITY;	// px per second

protected:
    sf::Vector2f m_direction;
    MotionState m_motionState = None;
    sf::Clock m_motionDuration;

	const float m_xvel = 500.f;	// px per second
	const float m_yvel = 500.f;	// px per second
    const float m_middleMotionState = 0.2f; // Entity stable speed after 100ms of motion
	const float m_finalMotionEnd = 0.2f;	// Entity will no longer move 100ms after key release
	sf::Vector2f m_movement;
};
