#include "animation.h"

Animation::Animation()
{
	currentDirection = right;
}

Animation::Animation(sf::String filename, uint count, int left, int top, int width, int height)
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

void Animation::getNextSprite()
{
	if (currentDirection == right)
	{
		//if move direction - right : read texture as it is (from left to right)
		if (spriteRect.left >= texture.get()->getSize().x - spriteWidth)
			spriteRect.left = 0;
		else
			spriteRect.left += spriteWidth;
	}
	else
	{
		//if move direction - right : read texture backward (from right to left)
		if (spriteRect.left <= spriteWidth)
			spriteRect.left = texture.get()->getSize().x;
		else
			spriteRect.left -= spriteWidth;
	}

	sprite.get()->setTextureRect(spriteRect);
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

sf::Sprite& Animation::getCurrentSprite()
{
	return *sprite.get();
}

void Animation::setScale(float scale)
{
	sprite.get()->setScale(scale, scale);
}

void Animation::setDirection(Direction direction)
{
	if (currentDirection != direction)
	{
		currentDirection = direction;
		//sprite.get()->setScale(-1.f, 1.f);
		spriteRect.width = -spriteRect.width;
	}
}
