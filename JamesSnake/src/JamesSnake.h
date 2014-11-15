#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <vector>
#include "time.h"

#include "SnakeSegment.h"

#include "SnakeUtil.h"

using namespace snake;



class JamesSnake
{
public:

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	SDL_Renderer* gRenderer;

	TTF_Font *gFont;

	int tW, tH;
	
	std::string nameBuffer;
	std::string userName;

	class LTexture
	{
	public:

		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font *gFont);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		SDL_Texture* mTexture;

		//The window renderer

		int mWidth;
		int mHeight;

	private:
		//The actual hardware texture
		

		//Image dimensions

	};

	//Main loop flag
	bool quit = false;

	bool menuStart = true;

	bool gettingName = false;

	bool gameOver = false;

	bool settingsMenu = false;

	//
	bool pause = false;

	int buttonSelection = 1;

	int bonusTimer = 0;

	int cursorBlinkTimer = 0;

	//
	int score = 0;
	int bestScore = 0;
	std::string mapName = "Meadow";

	//Event handler
	SDL_Event e;


	SDL_Rect food;
	SDL_Rect bonusFood;

	//Scene textures
	LTexture gObstacleTexture;
	LTexture gHeadTexture;
	LTexture gSegmentTexture;
	LTexture gKeyTexture;

	LTexture gScoreTextTexture;
	LTexture gMapTextTexture;
	LTexture gBestTextTexture;
	LTexture gBonusTextTexture;


	LTexture gGameOverTextTexture;
	LTexture gEnterNameTexture;
	LTexture gNameBufferTexture;

	LTexture gButtonPlayTextTexture;
	LTexture gButtonSettingsTextTexture;
	LTexture gButtonHighScoresTextTexture;

	LTexture gButtonSelectTexture;
	


	 std::vector<SnakeSegment> segments;
	 
	 std::vector<SDL_Rect> obstacles;


	static JamesSnake& getInstance();
	~JamesSnake();


	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	void start();

	void setGameText();

	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//
	void handleEvent(SDL_Event& e);

	int getBlockPos(int aPos);

	//
	void spawnFood();

	//
	void spawnBonusFood();

	//
	void addSnakeSegment();

	//
	void renderSnake();

	//
	void updateSnake();

	//
	void mainGameLoop();

	//static int threadFunction(void* data);

	void showButtonMenu(int buttonSelected);

	void setupObstacles();

	void renderObstacles();

	void checkObstacleCollision();

	void checkBoundaryCollision();

	void getUserName();

	void mainMenuLoop();
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







