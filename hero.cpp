#include "hero.h"

#include <cassert>

Hero::Hero()
{
}

void Hero::setAnimatedAction(HeroAction action, sf::String texture,
					 uint count, int left, int top, int width, int height,
					 float scale)
{
	auto pointer = std::make_shared<Animation>(
				Animation(texture, count, left, top, width, height));
	pointer.get()->setScale(scale);
	animatedActions[action] = pointer;
}

void Hero::nextMove()
{
	animatedActions.find(currentAction)->second.get()->getNextSprite();
}

bool Hero::changeActionTo(HeroAction action, Direction direction)
{
	auto wantedAction = animatedActions.find(action);
	assert(wantedAction != animatedActions.end());
	currentAction = action;
	wantedAction->second.get()->setDirection(direction);
	nextMove();
}

sf::Sprite& Hero::getSprite()
{
	return animatedActions.find(currentAction)->second.get()->getCurrentSprite();
}
