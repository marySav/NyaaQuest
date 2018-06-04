#ifndef HERO_H
#define HERO_H

#include <map>

#include <SFML/Graphics.hpp>

#include "animation.h"


enum Properties:int
{
	heroWidth = 542,
	heroHeight = 474
};

enum HeroAction:int
{
	run
};

class Hero
{
	public:
		Hero();
		sf::Sprite& getSprite();
		void setAnimatedAction(HeroAction action, sf::String texture,
					   uint count, int left, int top, int width, int height);
		void nextMove();
		void changeActionTo(HeroAction action);


	private:
		std::map<HeroAction, std::shared_ptr<Animation>> animatedActions;
		HeroAction currentAction;

		uint radius;
		int centerX;
		int centerY;

};

#endif // HERO_H
