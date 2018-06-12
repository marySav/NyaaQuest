#ifndef HERO_H
#define HERO_H

#include <map>

#include <SFML/Graphics.hpp>

#include "animation.h"

const float heroScale = 0.25;

const sf::Vector2f gravity(0, 0.0000002);
const sf::Vector2f jumpSpeed(0, -0.006);


enum Properties:int
{
	heroWidth = 542,
	heroHeight = 474,
	step = 3
};

enum class HeroAction:int
{
	idle, run,
	jump, slide, fall,
	dead, hurt
};

class Hero
{
	public:
		Hero(sf::RenderWindow * window);

		void initPosition();

		void setAnimatedAction(HeroAction action, sf::String filename,
					   uint count, int left, int top, int width, int height, float scale);

		bool changeDirection(Direction direction);
		bool jump();

		bool stopMovingTo(Direction direction);

		void draw(sf::Int32 millisec);

		Direction getDirection();


	private:
		bool changeActionTo(HeroAction action, Direction direction);

		bool isMovingVert();
		bool isMovingHoris();
		void updateY(sf::Int32 deltaTime);

		void landOnGround();
		bool isOnGround();

		void updateX();

		std::map<HeroAction, std::shared_ptr<Animation>> animatedActions;
		HeroAction currentAction;
		Direction currentDirection;
		Animation* getCurrentAction();

		sf::RenderWindow * window;

		uint radius;
		sf::Vector2f center;
		int width;
		int height;

		sf::Vector2f speed;

		uint ground;

};

#endif // HERO_H
