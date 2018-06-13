#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Hero;

class Game
{
	public:
		Game(sf::RenderWindow * window_);

		void init();

		void update();
		void display();
		sf::Int32 getTick();

		Hero* getHero();

	private:
		sf::RenderWindow * window;
		sf::Clock clock;

		Hero * cat;


};

#endif // GAME_H
