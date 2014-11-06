#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "SnakeUtil.h"

using namespace snake;

//The dot that will move around on the screen
class SnakeSegment
{
public:


	//Maximum axis velocity of the dot
	//static const int DOT_VEL = 20;

	//Initializes the variables
	SnakeSegment();

	//Takes key presses and adjusts the dot's velocity
	//void handleEvent(SDL_Event& e);

	//Moves the dot and checks collision
	void move();

	//Shows the dot on the screen

	int moveFactor = 0;

	int mPosX, mPosY;
	int mVelX, mVelY;

	int mVelXPrev, mVelYPrev;
	int mPosXPrev, mPosYPrev;

	int mDirection;

	SDL_Rect mCollider;

private:
	//The X and Y offsets of the dot


	//The velocity of the dot


	//SnakeSegment's collision box
	
};