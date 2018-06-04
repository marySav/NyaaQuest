#include "hero.h"

Hero::Hero()
{
}

void Hero::setAnimatedAction(HeroAction action, sf::String texture,
					 uint count, int left, int top, int width, int height)
{
	auto pointer = std::make_shared<Animation>(
				Animation(texture, count, left, top, width, height));
	animatedActions[action] = pointer;
}

void Hero::nextMove()
{
	animatedActions.find(currentAction)->second.get()->getNextSprite();
}

void Hero::changeActionTo(HeroAction action)
{
	currentAction = action;
	nextMove();
}

sf::Sprite& Hero::getSprite()
{
	return animatedActions.find(currentAction)->second.get()->getCurrentSprite();
}
