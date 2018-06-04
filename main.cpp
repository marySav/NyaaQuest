#include <iostream>

#include <SFML/Graphics.hpp>

#include "hero.h"

int main(int argc, char *argv[])
{
	float size = 600;
	sf::RenderWindow window(sf::VideoMode(size, size), "Nyaa Quest");

	//test shape drawing
	sf::CircleShape shape(size/2);
	shape.setFillColor(sf::Color::Cyan);

	//font load only once
	sf::Font font;
	font.loadFromFile("fonts/Purisa.ttf");


	//create cat hero
	Hero cat;
	cat.setAnimatedAction(run, "images/Run.png", 8, 0, 0, (int)heroWidth, (int)heroHeight);
	cat.changeActionTo(run);

	//clock for changing hero`s sprites
	sf::Clock clock;

	//main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//handle every supported event
			switch (event.type)
			{

				//close window
				case sf::Event::Closed:
					window.close();
					break;

				//mouse wheel
				case sf::Event::MouseWheelScrolled:
					break;

				//window resize
				case sf::Event::Resized:
				{
					// update the view to the new size of the window
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
					break;
				}

					//unsupported event
				default:
					break;
			}
		}

		//test text printing

		sf::Text text;
		// select the font
		text.setFont(font); // font is a sf::Font
		// set the string to display
		sf::String content = "Hello Nyaa world ^.^";
		text.setString(content);
		// set the character size
		int height = 24;
		text.setCharacterSize(height); // in pixels, not points!
		// set the color
		text.setColor(sf::Color::Red);
		text.setPosition(window.getSize().x / 2 - (text.findCharacterPos(content.getSize()-1).x / 2),
						 window.getSize().y / 2 - height / 2);

		if (clock.getElapsedTime().asSeconds() > 1/10.f){
			cat.nextMove();
			clock.restart();
		}

		window.clear();
		window.draw(shape);
		window.draw(cat.getSprite());
		window.draw(text);
		window.display();
	}

	return 0;
}
