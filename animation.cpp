#include "animation.h"

#include <iostream>

#include "direction.h"

Animation::Animation()
{
	currentSide = SideToRead::left;
}

Animation::Animation(const sf::String& filename,
					 uint count, int left, int top, int width, int height)
	: Animation()
{
	sprite = std::make_unique<sf::Sprite>(sf::Sprite());
	texture = std::make_unique<sf::Texture>(sf::Texture());
	setTexture(filename);
	spriteCount = count;
	currentSide = SideToRead::left;

	setFirstPosition(left, top, width, height);
}

Animation::Animation(Animation && source)
{
	this->sprite = std::move(source.sprite);
	this->spriteCount = std::move(source.spriteCount);
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
	sf::IntRect spriteRect = sprite->getTextureRect();
	spriteRect.left = left;
	spriteRect.top = top;
	spriteRect.width = width;
	spriteRect.height = height;
	sprite->setTextureRect(spriteRect);

	spriteWidth = width;
}

void Animation::setTexture(const sf::String& filename)
{
	texture.get()->loadFromFile(filename);
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
	return *sprite.get();
}

void Animation::setSpriteByNum(uint num)
{
	sf::IntRect spriteRect = sprite->getTextureRect();
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
	sf::IntRect spriteRect = sprite->getTextureRect();
	width = spriteRect.width * sprite->getScale().x;
	height = spriteRect.height * sprite->getScale().y;
}
