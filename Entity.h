#pragma once

#include <SFML/Graphics.hpp>


class Entity : public sf::Sprite
{
public:
	Entity(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position, const sf::Vector2f& velocity);
	virtual ~Entity();
	
protected:
	sf::Vector2f m_velocity;
};