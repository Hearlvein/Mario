#include "Mario.h"
#include <iostream>

Mario::Mario() : Entity()
{
	setTexture(sf::Texture());
	setTextureRect(sf::IntRect(0, 0, 50, 50));
	setPosition(250, 100);
}

Mario::~Mario()
{
}

void Mario::fire()
{
	std::cout << "Fire!" << std::endl;
}
