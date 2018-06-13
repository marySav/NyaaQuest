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

const int timeForSingleFrame = 100;

class Animation : private boost::noncopyable
{
	public:
		Animation();

		//constructor for init new animation
		Animation(sf::String filename,
				  uint count, int left, int top, int width, int height);

		//move constructor to prevent copy in std::map
		Animation(Animation&& source);

		void setSpriteCount(uint count);
		void setFirstPosition(int left, int top, int width, int height);
		void setTexture(sf::String filename);
		void setScale(float scale);
		void readStraight();
		void readReverse();

		sf::Sprite& getSpriteAt(sf::Int32 millisec);

		void getSize(int & width, int & height);

	private:
		uint spriteCount;
		sf::IntRect spriteRect;
		std::shared_ptr<sf::Sprite> sprite;
		std::shared_ptr<sf::Texture> texture;
		int spriteWidth;
		SideToRead currentSide;

		void setSpriteByNum(uint num);
};

#endif // ANIMATION_H
