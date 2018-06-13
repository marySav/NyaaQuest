#include <iostream>

#include <SFML/Graphics.hpp>

#include "game.h"
#include "inputhandlerhero.h"

const int TICKS_PER_SECOND = 50;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 10;

int main(int argc, char *argv[])
{
	int winWidth = 800;
	int winHeight = 600;
	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Nyaa Quest");
	//set appropriate time to sleep after window.display()
	//window.setFramerateLimit(60);

	Game game(&window);
	InputHandlerHero handler(&window, game.getHero());

	sf::Int32 nextTick = game.getTick();
	int loops = 0;

	//main loop
	while (window.isOpen())
	{
		loops = 0;
		while (game.getTick() > nextTick && loops < MAX_FRAMESKIP)
		{
			handler.getKeyboardInput();
			game.update();

			nextTick += SKIP_TICKS;
			++loops;
		}
		game.display();
	}
	return 0;
}
