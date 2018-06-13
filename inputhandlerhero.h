#ifndef INPUTHANDLERHERO_H
#define INPUTHANDLERHERO_H

#include <SFML/Graphics.hpp>

class Hero;

class InputHandlerHero
{
	public:
		InputHandlerHero(sf::RenderWindow * window_, Hero * cat_);
		
		bool getKeyboardInput();
	
	private:
		sf::RenderWindow * window;
		Hero * cat;
};

#endif // INPUTHANDLERHERO_H
