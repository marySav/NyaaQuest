#include <iostream>

#include <SFML/Graphics.hpp>

#include "hero.h"

int main(int argc, char *argv[])
{
	int winWidth = 800;
	int winHeight = 600;
	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Nyaa Quest");
	//set appropriate time to sleep after window.display()
	window.setFramerateLimit(60);

	//create cat hero
	Hero cat;
	//set all possible textures for each action
	cat.setAnimatedAction(run, "images/Run.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(slide, "images/Slide.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(jump, "images/Jump.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(dead, "images/Dead.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(hurt, "images/Hurt.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(fall, "images/Fall.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(idle, "images/Idle.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.changeActionTo(run, left);

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

					//text entry
				case sf::Event::TextEntered:
				{
					switch (event.text.unicode)
					{
						case 'a':
							cat.changeActionTo(run, left);
							break;
						case 'd':
							cat.changeActionTo(run, right);
							break;
					}

					break;
				}

					//unsupported event
				default:
					break;
			}
		}

		if (clock.getElapsedTime().asSeconds() > 1/10.f){
			cat.nextMove();
			clock.restart();
		}

		window.clear();
		window.draw(cat.getSprite());
		window.display();
	}

	return 0;
}
