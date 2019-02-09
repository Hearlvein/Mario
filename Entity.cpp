#include "Entity.h"


Entity::Entity(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position, const sf::Vector2f& velocity) :
	sf::Sprite(texture, rectangle), m_velocity(velocity)
{
	setPosition(position);
}

Entity::~Entity()
{

}