#include "hero.h"

#include <cassert>

#include "direction.h"
#include "animation.h"

Hero::Hero(sf::RenderWindow* window)
	: window(window),
	  radius(0),
	  ground(400)
{
	speed.x = 0;
	speed.y = 0;
}

Hero::~Hero()
{
	animatedActions.clear();
}

void Hero::initPosition()
{
	if (radius == 0)
		return;

	//hero will start from top left corner
	//so he will fall
	center.x = radius;
	center.y = radius;
	if (center.y + radius < ground)
		changeActionTo(HeroAction::fall, Direction::none);
}

void Hero::setAnimatedAction(HeroAction action, const sf::String& filename,
							 uint count, int left, int top, int width, int height,
							 float scale)
{
	animatedActions[action] = std::make_unique<Animation>(
				filename, count, left, top, width, height);
	animatedActions[action]->setScale(scale);
	size = animatedActions[action]->getSize();
	if (radius < size.x / 2 || radius < size.y / 2)
	{
		radius = (size.x > size.y) ? size.x : size.y;
		radius /= 2;
	}
}

bool Hero::changeDirection(Direction direction)
{
	if (!isOnGround())
		return false;
	//need start running or just change direction
	HeroAction action = currentAction == HeroAction::idle ?
				HeroAction::run : currentAction;
	return changeActionTo(action, direction);
}

bool Hero::jump()
{
	if (!isOnGround())
		return false;
	return changeActionTo(HeroAction::jump, currentDirection);
}

//returns if action was changed
bool Hero::changeActionTo(HeroAction action, Direction direction)
{
	//don`t need to do anything if action already active
	//or player trying to move in middle air
	if (action == currentAction)
		return false;

	//reset timer for proper animation and actions like jump
	actionStart = -1;

	auto wantedAction = animatedActions.find(action);
	assert(wantedAction != animatedActions.end());
	currentAction = action;
	currentDirection = direction;
	if(currentDirection == Direction::left)
		wantedAction->second->readReverse();
	else if (currentDirection == Direction::right)
		wantedAction->second->readStraight();

	if (currentAction == HeroAction::jump)
	{
		//set speed acording to oy
		assert(isOnGround());
		speed.y = jumpSpeed.y;
	}
	return true;
}

void Hero::updateY(sf::Int32 deltaTime)
{
	if (!isOnGround() && !isMovingVert())
		changeActionTo(HeroAction::fall, currentDirection);
	if (isMovingVert())
	{
		center += ((float)deltaTime) * speed;
		speed += ((float)deltaTime) * gravity;

		//need to skip first moment when hero didn`t have time to jump
		if (deltaTime != 0 && center.y + radius >= ground)
			landOnGround();
	}
}

void Hero::updateX()
{
	if (isMovingHoris())
	{
		if (currentDirection == Direction::left)
			center.x -= step;
		else
			center.x += step;
	}
}

void Hero::update(sf::Int32 millisec)
{
	if (actionStart < 0)
		actionStart = millisec;
	updateX();
	updateY(millisec - actionStart);
}

void Hero::draw(sf::Int32 millisec)
{
	sf::Sprite spriteToDraw = getCurrentAction()->
			getSpriteAt(millisec - actionStart);
	spriteToDraw.setPosition(center.x - radius, center.y - radius);
	window->draw(spriteToDraw);
}

Animation* Hero::getCurrentAction()
{
	auto animation =  animatedActions.find(currentAction);
	assert(animation != animatedActions.end());
	return animation->second.get();
}

bool Hero::isMovingVert()
{
	return  currentAction == HeroAction::jump ||
			currentAction == HeroAction::fall;
}

bool Hero::isMovingHoris()
{
	return  currentAction == HeroAction::run ||
			currentAction == HeroAction::slide ||
			(currentAction == HeroAction::jump && currentDirection != Direction::none);
}

Direction Hero::getDirection()
{
	return currentDirection;
}

bool Hero::stopMovingTo(Direction direction)
{
	//check if we moving in given direction
	if (isMovingHoris() && currentDirection == direction)
	{
		changeActionTo(HeroAction::idle, Direction::none);
		return true;
	}
	return false;
}

void Hero::landOnGround()
{
	center.y = ground - radius;
	speed.y = 0;

	//if hero were jumping and running we need still running
	if (currentAction == HeroAction::jump &&
			currentDirection != Direction::none)
		changeActionTo(HeroAction::run, currentDirection);
	else
		changeActionTo(HeroAction::idle, Direction::none);
}

bool Hero::isOnGround()
{
	return ground - radius == center.y;
}
