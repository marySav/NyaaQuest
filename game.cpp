#include "game.h"

#include "hero.h"

Game::Game(sf::RenderWindow* window_)
	: window(window_)
{
	init();
}


void Game::init()
{
	//create cat hero
	cat = new Hero(window);
	//set all possible textures for each action
	cat->setAnimatedAction(HeroAction::run, "images/Run.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat->setAnimatedAction(HeroAction::slide, "images/Slide.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat->setAnimatedAction(HeroAction::jump, "images/Jump.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat->setAnimatedAction(HeroAction::dead, "images/Dead.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat->setAnimatedAction(HeroAction::hurt, "images/Hurt.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat->setAnimatedAction(HeroAction::fall, "images/Fall.png", 8, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat->setAnimatedAction(HeroAction::idle, "images/Idle.png", 10, 0, 0,
						  heroWidth, heroHeight, heroScale);
	cat->initPosition();
}

Hero* Game::getHero()
{
	return cat;
}

void Game::update()
{
	cat->update(getTick());
}

void Game::display()
{
	window->clear();
	cat->draw(getTick());
	window->display();
}

sf::Int32 Game::getTick()
{
	return clock.getElapsedTime().asMilliseconds();
}
