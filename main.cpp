#include "Game.h"

int main()
{
	sf::Clock tick;
	Game game;

    sf::RenderWindow window(game.getWindowSize(), "Mario");
	//window.setFramerateLimit(60);

	bool update = true;
	int numberFrames = 0;

	while (window.isOpen())
	{
		game.processEvents(window);
		if (update)
		{
			//numberFrames++;
			game.update(tick.restart().asSeconds(), window);

			/*if (numberFrames > 100)
            {
                update = false;
                system("pause");
            }*/
		}
		game.render(window);
		window.display();
	}
}
