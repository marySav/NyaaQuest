#ifndef HERO_H
#define HERO_H

#include <map>

#include <SFML/Graphics.hpp>

#include "animation.h"

const float heroScale = 0.25;

enum Properties:int
{
	heroWidth = 542,
	heroHeight = 474
};

enum HeroAction:int
{
	idle, run,
	jump, slide, fall,
	dead, hurt
};

class Hero
{
	public:
		Hero();
		sf::Sprite& getSprite();
		void setAnimatedAction(HeroAction action, sf::String texture,
					   uint count, int left, int top, int width, int height, float scale);
		void nextMove();
		bool changeActionTo(HeroAction action, Direction direction);


	private:
		std::map<HeroAction, std::shared_ptr<Animation>> animatedActions;
		HeroAction currentAction;
		Direction currentDirection;

		uint radius;
		int centerX;
		int centerY;

};

#endif // HERO_H
