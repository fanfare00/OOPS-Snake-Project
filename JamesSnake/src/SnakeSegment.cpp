#include "SnakeSegment.h"


SnakeSegment::SnakeSegment()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Set collision box dimension
	mCollider.w = SEGMENT_WIDTH;
	mCollider.h = SEGMENT_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	mDirection = SNAKE_DIRECTION_RIGHT;


}



void SnakeSegment::move()
{


	//SDL_Delay(100);

	SDL_Delay(GAME_STEP_RATE);
	moveFactor += 100;

	mPosXPrev = mPosX;
	mPosYPrev = mPosY;


	//move snake head and colider right


	//mPosXPrev = 100;
	//mPosYPrev = 100;

	if (moveFactor > 1000)
	{
		//mPosXPrev = mPosX;
		//mPosYPrev = mPosY;

		switch (mDirection)
		{
		case SNAKE_DIRECTION_UP:
			mPosY -= 40;
			break;

		case SNAKE_DIRECTION_DOWN:
			mPosY += 40;
			break;

		case SNAKE_DIRECTION_LEFT:
			mPosX -= 40;
			break;

		case SNAKE_DIRECTION_RIGHT:
			mPosX += 40;
			break;
		}

		moveFactor = 0;
	}


	

	mCollider.x = mPosX;
	mCollider.y = mPosY;




}

