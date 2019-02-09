#pragma once

#include "Entity.h"


class Mario : public Entity
{
public:
	Mario(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position, const sf::Vector2f& velocity);
	~Mario();
	
	void fire();
};