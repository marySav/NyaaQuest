#include "inputhandlerhero.h"

#include "direction.h"
#include "hero.h"

InputHandlerHero::InputHandlerHero(sf::RenderWindow* window_, Hero* cat_)
	: window(window_),
	  cat(cat_)
{
}

bool InputHandlerHero::getKeyboardInput()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		//handle every supported event
		switch (event.type)
		{

			//close window
			case sf::Event::Closed:
				window->close();
				break;

				//mouse wheel
			case sf::Event::MouseWheelScrolled:
				break;

				//window resize
			case sf::Event::Resized:
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window->setView(sf::View(visibleArea));
				break;
			}
				//key press event : change action
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
					case sf::Keyboard::A:
						cat->changeDirection(Direction::left);
						break;
					case sf::Keyboard::D:
						cat->changeDirection(Direction::right);
						break;
					case sf::Keyboard::W:
						cat->jump();
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
						cat->stopMovingTo(Direction::left);
						break;
					case sf::Keyboard::D:
						cat->stopMovingTo(Direction::right);
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
}
