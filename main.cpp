#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mario");
	sf::Clock tick;
	Game game;

	while (window.isOpen())
	{
		game.processEvents(window);
		game.update(tick.getElapsedTime());
		game.render(window);
		window.display();
	}
}
