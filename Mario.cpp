#include "Mario.h"
#include <iostream>

Mario::Mario(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position, const sf::Vector2f& velocity) :
	Entity(texture, rectangle, position, velocity)
{

}

Mario::~Mario()
{

}
	
void Mario::fire()
{
	std::cout << "Fire!" << std::endl;
