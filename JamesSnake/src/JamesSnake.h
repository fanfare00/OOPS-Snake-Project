#ifndef JAMESSNAKE_H
#define JAMESSNAKE_H



#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <vector>
#include "time.h"


#include "LTexture.h"
#include "SnakeSegment.h"





class JamesSnake
{
public:

	const int SNAKE_DIRECTION_UP = 1;
	const int SNAKE_DIRECTION_DOWN = 2;
	const int SNAKE_DIRECTION_LEFT = 3;
	const int SNAKE_DIRECTION_RIGHT = 4;

	//Screen dimension constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//The dimensions of the dot
	const int SEGMENT_WIDTH = 40;
	const int SEGMENT_HEIGHT = 40;

	const int GAME_STEP_RATE = 10;

	const int GAME_FIELD_WIDTH = SCREEN_WIDTH - SEGMENT_WIDTH * 2;
	const int GAME_FIELD_HEIGHT = SCREEN_HEIGHT - SEGMENT_HEIGHT * 3;
	const int GAME_FIELD_XPOS = SEGMENT_WIDTH;
	const int GAME_FIELD_YPOS = SEGMENT_HEIGHT * 2;

	LTexture gTextTexture;

	//Snake direction constants


	//Main loop flag
	bool quit = false;

	//
	bool pause = false;


	//Event handler
	SDL_Event e;


	SDL_Rect food;

	//Scene textures
	LTexture gSegmentTexture;

	 std::vector<SnakeSegment> segments;


	static JamesSnake& getInstance();
	~JamesSnake();


	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	void start();

	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//
	void handleEvent(SDL_Event& e);

	int getBlockPos(int aPos);

	//
	void spawnFood();

	//
	void addSnakeSegment();

	//
	void renderSnake();

	//
	void updateSnake();

	//
	void mainGameLoop();

	//static int threadFunction(void* data);

	
};


//#ifdef _SDL_TTF_H
//bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
//{
//	//Get rid of preexisting texture
//	free();
//
//	//Render text surface
//	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
//	if (textSurface != NULL)
//	{
//		//Create texture from surface pixels
//		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//		if (mTexture == NULL)
//		{
//			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
//		}
//		else
//		{
//			//Get image dimensions
//			mWidth = textSurface->w;
//			mHeight = textSurface->h;
//		}
//
//		//Get rid of old surface
//		SDL_FreeSurface(textSurface);
//	}
//	else
//	{
//		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
//	}
//
//
//	//Return success
//	return mTexture != NULL;
//}
//#endif



#endif /* JAMESSNAKE_H */



