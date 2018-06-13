#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>

#include <SFML/Graphics.hpp>

//just to check copyable
#include <boost/core/noncopyable.hpp>

enum class SideToRead
{
	left, right
};


class Animation : private boost::noncopyable
{
	public:
		Animation();

		//constructor for init new animation
		Animation(const sf::String & filename,
				  uint count, int left, int top, int width, int height);

		void setSpriteCount(uint count);
		void setFirstPosition(int left, int top, int width, int height);
		void setTexture(const sf::String & filename);
		void setScale(float scale);
		void readStraight();
		void readReverse();

		sf::Sprite& getSpriteAt(sf::Int32 millisec);

		sf::Vector2i getSize();

	private:
		uint spriteCount;
		std::unique_ptr<sf::Sprite> sprite;
		std::unique_ptr<sf::Texture> texture;
		int spriteWidth;
		SideToRead currentSide;

		void setSpriteByNum(uint num);
};

#endif // ANIMATION_H
