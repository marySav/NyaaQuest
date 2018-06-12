#include "animation.h"

Animation::Animation()
{
	currentDirection = Direction::right;
}

Animation::Animation(sf::String filename,
					 uint count, int left, int top, int width, int height)
	: Animation()
{
	sprite = std::make_shared<sf::Sprite>(sf::Sprite());
	texture = std::make_shared<sf::Texture>(sf::Texture());
	setTexture(filename);
	spriteCount = count;

	setFirstPosition(left, top, width, height);
}

Animation::Animation(Animation && source)
{
	this->sprite = std::move(source.sprite);
	this->spriteCount = std::move(source.spriteCount);
	this->spriteRect = std::move(source.spriteRect);
	this->spriteWidth = std::move(source.spriteWidth);
	this->texture = std::move(source.texture);
	this->currentDirection= std::move(source.currentDirection);
}

void Animation::setSpriteCount(uint count)
{
	spriteCount = count;
}

void Animation::setFirstPosition(int left, int top, int width, int height)
{
	//set position of first sprite
	spriteRect.left = left;
	spriteRect.top = top;
	spriteRect.width = width;
	spriteRect.height = height;

	spriteWidth = width;
}

void Animation::setTexture(sf::String filename)
{
	texture.get()->loadFromFile(filename);
	if (sprite.get() != nullptr)
		sprite.get()->setTexture(*texture.get());
}

void Animation::setScale(float scale)
{
	sprite.get()->setScale(scale, scale);
}

void Animation::setDirection(Direction direction)
{
	//if dont need to move ox - remain previous direction
	if (direction == Direction::none)
		return;

	if (currentDirection != direction)
	{
		currentDirection = direction;
		spriteRect.width = -spriteRect.width;
	}
}

sf::Sprite& Animation::getSpriteAt(sf::Int32 millisec)
{
	//skeep some frames (60 fps is super fast for these spritesheets)
	uint neededSpriteNum = millisec % (spriteCount * timeForSingleFrame) / timeForSingleFrame;
	setSpriteByNum(neededSpriteNum);
	return *sprite.get();
}

void Animation::setSpriteByNum(uint num)
{
	if (currentDirection == Direction::right)
	{
		//if move direction - right : read texture as it is (from left to right)
		spriteRect.left = num * spriteWidth;
	}
	else
	{
		//if move direction - right : read texture backward (from right to left)
		spriteRect.left = (num + 1) * spriteWidth;
	}

	sprite.get()->setTextureRect(spriteRect);
}

void Animation::getSize(int & width, int & height)
{
	width = spriteRect.width * sprite.get()->getScale().x;
	height = spriteRect.height * sprite.get()->getScale().y;
}
