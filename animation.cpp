#include "animation.h"

Animation::Animation()
{
}

Animation::Animation(sf::String filename, uint count, int left, int top, int width, int height)
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
}

void Animation::setSpriteCount(uint count)
{
	spriteCount = count;
}

void Animation::getNextSprite()
{
	if (spriteRect.left >= texture.get()->getSize().x - spriteWidth)
		spriteRect.left = 0;
	else
		spriteRect.left += spriteWidth;

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

