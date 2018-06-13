#include "animation.h"

#include <iostream>

#include "direction.h"

Animation::Animation()
{
	currentSide = SideToRead::left;
}

Animation::Animation(sf::String filename,
					 uint count, int left, int top, int width, int height)
	: Animation()
{
	sprite = std::make_shared<sf::Sprite>(sf::Sprite());
	texture = std::make_shared<sf::Texture>(sf::Texture());
	setTexture(filename);
	spriteCount = count;
	currentSide = SideToRead::left;

	setFirstPosition(left, top, width, height);
}

Animation::Animation(Animation && source)
{
	this->sprite = std::move(source.sprite);
	this->spriteCount = std::move(source.spriteCount);
	this->spriteRect = std::move(source.spriteRect);
	this->spriteWidth = std::move(source.spriteWidth);
	this->texture = std::move(source.texture);
	this->currentSide= std::move(source.currentSide);
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
		sprite->setTexture(*texture.get());
}

void Animation::setScale(float scale)
{
	sprite->setScale(scale, scale);
}

void Animation::readReverse()
{
	currentSide = SideToRead::right;
}

void Animation::readStraight()
{
	currentSide = SideToRead::left;
}

sf::Sprite& Animation::getSpriteAt(sf::Int32 millisec)
{
	//skeep some frames (60 fps is super fast for these spritesheets)
	uint neededSpriteNum = millisec % (spriteCount * timeForSingleFrame) / timeForSingleFrame;
	setSpriteByNum(neededSpriteNum);
	//std::cout << neededSpriteNum << std::endl;
	return *sprite.get();
}

void Animation::setSpriteByNum(uint num)
{
	if (currentSide == SideToRead::left)
	{
		//if move direction - right : read texture as it is (from left to right)
		spriteRect.left = num * spriteWidth;
		spriteRect.width = abs(spriteRect.width);
	}
	else
	{
		//if move direction - right : read texture backward (from right to left)
		spriteRect.left = (num + 1) * spriteWidth;
		spriteRect.width = -abs(spriteRect.width);
	}

	sprite->setTextureRect(spriteRect);
}

void Animation::getSize(int & width, int & height)
{
	width = spriteRect.width * sprite->getScale().x;
	height = spriteRect.height * sprite->getScale().y;
}
