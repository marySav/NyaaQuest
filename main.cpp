#include <iostream>

#include <SFML/Graphics.hpp>

#include "hero.h"
#include "direction.h"

int main(int argc, char *argv[])
{
	int winWidth = 800;
	int winHeight = 600;
	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Nyaa Quest");
	//set appropriate time to sleep after window.display()
	window.setFramerateLimit(60);

	//create cat hero
	Hero cat(&window);
	//set all possible textures for each action
	cat.setAnimatedAction(HeroAction::run, "images/Run.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(HeroAction::slide, "images/Slide.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(HeroAction::jump, "images/Jump.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(HeroAction::dead, "images/Dead.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(HeroAction::hurt, "images/Hurt.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(HeroAction::fall, "images/Fall.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.setAnimatedAction(HeroAction::idle, "images/Idle.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat.initPosition();

	//clock for changing hero`s sprites
	sf::Clock clock;
	int frames = 0;

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
					//key press event : change action
				case sf::Event::KeyPressed:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::A:
							if (cat.changeDirection(Direction::left))
								clock.restart();
								//frames = 0;
							break;
						case sf::Keyboard::D:
							if (cat.changeDirection(Direction::right))
								clock.restart();
								//frames = 0;
							break;
						case sf::Keyboard::W:
							if (cat.jump())
								clock.restart();
								//frames = 0;
							break;
						default:
							break;
					}
					break;
				}
					//key release event : change to idle
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
						case sf::Keyboard::A:
							if (cat.stopMovingTo(Direction::left))
								clock.restart();
								//frames = 0;
							break;
						case sf::Keyboard::D:
							if (cat.stopMovingTo(Direction::right))
								clock.restart();
								//frames = 0;
							break;
						default:
							break;
					}
					break;
					//unsupported event
				default:
					break;
			}
		}


		window.clear();
		//cat.draw(frames);
		cat.draw(clock.getElapsedTime().asMilliseconds());
		window.display();
		frames++;

	}

	return 0;
}
