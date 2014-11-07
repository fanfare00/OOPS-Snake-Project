#ifndef SNAKEUTIL_H
#define SNAKEUTIL_H




#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>


namespace snake
{
	const int SNAKE_DIRECTION_UP = 1;
	const int SNAKE_DIRECTION_DOWN = 2;
	const int SNAKE_DIRECTION_LEFT = 3;
	const int SNAKE_DIRECTION_RIGHT = 4;

	//Screen dimension constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	//The dimensions of the dot
	 const int SEGMENT_WIDTH = 40;
	 const int SEGMENT_HEIGHT = 40;

	 const int GAME_STEP_RATE = 10;

	 const int GAME_FIELD_WIDTH = SCREEN_WIDTH - SEGMENT_WIDTH * 2;
	 const int GAME_FIELD_HEIGHT = (SCREEN_HEIGHT - SEGMENT_HEIGHT * 3)-200;
	 const int GAME_FIELD_XPOS = SEGMENT_WIDTH;
	 const int GAME_FIELD_YPOS = SEGMENT_HEIGHT * 2;
	
}

#endif /* GRANDFATHER_H */