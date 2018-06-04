#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>

#include <SFML/Graphics.hpp>

//just to check copyable
#include <boost/core/noncopyable.hpp>

class Animation : private boost::noncopyable
{
	public:
		Animation();
		//constructor for init new animation
		Animation(sf::String filename, uint count, int left, int top, int width, int height);
		//move constructor to prevent copy in std::map
		Animation(Animation&& source);

		void setSpriteCount(uint count);
		void getNextSprite();
		void setFirstPosition(int left, int top, int width, int height);
		void setTexture(sf::String filename);
		sf::Sprite& getCurrentSprite();

	private:
		uint spriteCount;
		sf::IntRect spriteRect;
		std::shared_ptr<sf::Sprite> sprite;
		std::shared_ptr<sf::Texture> texture;
		int spriteWidth;
};

#endif // ANIMATION_H
