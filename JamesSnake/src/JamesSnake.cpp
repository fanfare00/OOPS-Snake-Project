#include "JamesSnake.h"


JamesSnake::~JamesSnake()
{
	//endwin();
}

JamesSnake& JamesSnake::getInstance()
{
	static JamesSnake instance;
	return instance;
}



bool JamesSnake::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("James' Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if ((gRenderer == NULL))
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool JamesSnake::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if (!gSegmentTexture.loadFromFile("dot.png", gRenderer))
	{
		printf("Failed to load segment texture!\n");
		success = false;
	}

	if (!gKeyTexture.loadFromFile("keyUpDown.png", gRenderer))
	{
		printf("Failed to load key texture!\n");
		success = false;
	}

	if (!gHeadTexture.loadFromFile("head.png", gRenderer))
	{
		printf("Failed to load head texture!\n");
		success = false;
	}

	if (!gObstacleTexture.loadFromFile("obstacle.png", gRenderer))
	{
		printf("Failed to load head texture!\n");
		success = false;
	}

	if (!gButtonSelectTexture.loadFromFile("selector.png", gRenderer))
	{
		printf("Failed to load selector texture!\n");
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("SlimJoe.ttf", 32);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{

		setGameText();
	}

	return success;
}

void JamesSnake::close()
{
	gMapTextTexture.free();

	gBestTextTexture.free();

	//Free loaded images
	gScoreTextTexture.free();

	gButtonPlayTextTexture.free();
	gButtonSettingsTextTexture.free();
	gButtonHighScoresTextTexture.free();

	//Free loaded images
	gSegmentTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool JamesSnake::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the food rectangle
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void JamesSnake::start()
{
	

	//gSegmentTexture.gWindow = gWindow_;
	//gSegmentTexture.gRenderer = gRenderer_;
	//gSegmentTexture.gFont = gFont_;

	//gTextTexture.gWindow = gWindow_;
	//gTextTexture.gRenderer = gRenderer_;
	//gTextTexture.gFont = gFont_;

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{


		}
	}
}

void JamesSnake::setGameText()
{

	//Render text
	SDL_Color textColor = {255, 255, 255 };
	if (!gScoreTextTexture.loadFromRenderedText("Score " + std::to_string(score), textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");
		
	}

	if (!gButtonPlayTextTexture.loadFromRenderedText("play", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}

	if (!gButtonSettingsTextTexture.loadFromRenderedText("settings", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}

	if (!gButtonHighScoresTextTexture.loadFromRenderedText("high scores", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}

	if (!gMapTextTexture.loadFromRenderedText(mapName, textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}

	if (!gBestTextTexture.loadFromRenderedText("Best " + std::to_string(bestScore), textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}

	textColor = { 255, 0, 0 };
	if (!gGameOverTextTexture.loadFromRenderedText("game over", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
}

void JamesSnake::handleEvent(SDL_Event& e)
{
	
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:

			if (menuStart)
			{
				if (buttonSelection > 1)
				{
					buttonSelection -= 1;
				}
				else
				{
					buttonSelection = 3;
				}
			}
			else if (segments[0].mDirection != SNAKE_DIRECTION_DOWN)
			{
				segments[0].mDirection = SNAKE_DIRECTION_UP;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();

				if (!gKeyTexture.loadFromFile("keyLeftRight.png", gRenderer))
				{
					printf("Failed to load dot texture!\n");
					
				}
	
			}
			break;

		case SDLK_DOWN:
			if (menuStart)
			{
				if (buttonSelection < 3)
				{
					buttonSelection += 1;
				}
				else
				{
					buttonSelection = 1;
				}
			}
			else if (segments[0].mDirection != SNAKE_DIRECTION_UP)
			{
				segments[0].mDirection = SNAKE_DIRECTION_DOWN;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();

				if (!gKeyTexture.loadFromFile("keyLeftRight.png", gRenderer))
				{
					printf("Failed to load dot texture!\n");

				}

			}
			break;

		case SDLK_LEFT:
			if (menuStart)
			{

			}
			else if (segments[0].mDirection != SNAKE_DIRECTION_RIGHT)
			{
				segments[0].mDirection = SNAKE_DIRECTION_LEFT;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();

				if (!gKeyTexture.loadFromFile("keyUpDown.png", gRenderer))
				{
					printf("Failed to load dot texture!\n");

				}

			}

			break;

		case SDLK_RIGHT:
			if (menuStart)
			{

			}
			else if (segments[0].mDirection != SNAKE_DIRECTION_LEFT)
			{
				segments[0].mDirection = SNAKE_DIRECTION_RIGHT;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();

				if (!gKeyTexture.loadFromFile("keyUpDown.png", gRenderer))
				{
					printf("Failed to load dot texture!\n");

				}

			}
			break;

		case SDLK_p:
			if (!gettingName)
			{
				if (!pause)
				{
					pause = true;
					printf("pause");
					printf((char*)userName.c_str());
				}
				else
				{
					pause = false;
					printf("NOT pause");
				}
			}
			break;

		case SDLK_r:
			if (!gettingName)
			{
				mainGameLoop();
			}
			break;

		case SDLK_BACKSPACE:
			if (gettingName)
			{
				if (nameBuffer.length() > 0)
				{
					nameBuffer.pop_back();

				}
				
			}

			break;

		case SDLK_RETURN:
			if (gettingName == true)
			{
				userName = nameBuffer;
				gettingName = false;
			}

			if ((menuStart == true))
			{
				if (buttonSelection == 1)
				{
					if (userName.length() == 0)
					{
						gettingName = true;
					}
					
					menuStart = false;
					mainGameLoop();
				}
				if (buttonSelection == 2)
				{
					menuStart = false;
					settingsMenu = true;
				}
			}
			break;
		}
	}

}

void JamesSnake::spawnFood()
{	

	//Set the food
	food.x = getBlockPos(((rand() % 10) * ((GAME_FIELD_WIDTH+SEGMENT_WIDTH) / 10)));
	food.y = SEGMENT_HEIGHT + getBlockPos(((rand() % 10) * ((GAME_FIELD_HEIGHT + SEGMENT_HEIGHT) / 10)));

	for (int i = 0; i < segments.size(); i++)
	{

		if ((food.x == segments[i].mCollider.x) && (food.y == segments[i].mCollider.y))
		{
			printf("DUPLICATE - SNAKE\n");
			spawnFood();
		}

	}

	for (int j = 0; j < obstacles.size(); j++)
	{
		if ((food.x == obstacles[j].x) && (food.y == obstacles[j].y))
		{
			printf("DUPLICATE - WALL\n");
			spawnFood();
		}
	}

	return;

}

void JamesSnake::spawnBonusFood()
{	
	printf("bonus spawned");

	//Set the food
	bonusFood.x = getBlockPos(((rand() % 10) * ((GAME_FIELD_WIDTH + SEGMENT_WIDTH) / 10)));
	bonusFood.y = SEGMENT_HEIGHT + getBlockPos(((rand() % 10) * ((GAME_FIELD_HEIGHT + SEGMENT_HEIGHT) / 10)));

	for (int i = 0; i < segments.size(); i++)
	{

		if ((bonusFood.x == segments[i].mCollider.x) && (bonusFood.y == segments[i].mCollider.y))
		{
			printf("DUPLICATE - SNAKE\n");
			spawnBonusFood();
		}

	}

	for (int j = 0; j < obstacles.size(); j++)
	{
		if ((bonusFood.x == obstacles[j].x) && (bonusFood.y == obstacles[j].y))
		{
			printf("DUPLICATE - WALL\n");
			spawnBonusFood();
		}
	}

	return;

}

void JamesSnake::addSnakeSegment()
{

		SnakeSegment k;
		k.mPosX = segments[segments.size()-1].mPosXPrev;
		k.mPosY = segments[segments.size() - 1].mPosYPrev;
		k.mPosXPrev = k.mPosX;
		k.mPosYPrev = k.mPosY;
		segments.push_back(k);

		printf("Size: %i \n\n", segments.size());

}

void JamesSnake::renderSnake()
{

	
	for (int i = 1; i < segments.size(); i++)
	{
		//Show the dot
		gSegmentTexture.render(gRenderer, segments[i].mPosX, segments[i].mPosY);
		
	}
	gHeadTexture.render(gRenderer, segments[0].mPosX, segments[0].mPosY);
}

void JamesSnake::updateSnake()
{


	if (segments.size() > 1)
	{
		if (segments[0].moveFactor == 1000)
		{
			for (int i = 1; i < segments.size(); i++)
			{

				segments[i].mPosXPrev = segments[i].mPosX;
				segments[i].mPosYPrev = segments[i].mPosY;

				segments[i].mPosX = segments[i - 1].mPosXPrev;
				segments[i].mPosY = segments[i - 1].mPosYPrev;

				segments[i].mCollider.x = segments[i].mPosX;
				segments[i].mCollider.y = segments[i].mPosY;

			}
		}
	}

}

int JamesSnake::getBlockPos(int aPos)
{
	return aPos + (SEGMENT_WIDTH - aPos % SEGMENT_WIDTH);
}



JamesSnake::LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

JamesSnake::LTexture::~LTexture()
{
	//Deallocate
	free();
}


int JamesSnake::LTexture::getWidth()
{
	return mWidth;
}

int JamesSnake::LTexture::getHeight()
{
	return mHeight;
}

void JamesSnake::LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void JamesSnake::LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void JamesSnake::LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void JamesSnake::LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

bool JamesSnake::LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont)
{

	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

bool JamesSnake::LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

//Get rid of old loaded surface
SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


void JamesSnake::LTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void JamesSnake::showButtonMenu(int buttonSelected)
{


	SDL_Rect b1;
	b1.w = SCREEN_WIDTH / 2;
	b1.h = 70;
	b1.x = SCREEN_WIDTH/4;
	b1.y = SCREEN_HEIGHT - SCREEN_HEIGHT/3.3;

	SDL_Rect b2;
	b2.w = SCREEN_WIDTH / 2;
	b2.h = 70;
	b2.x = 0 + SCREEN_WIDTH / 4;
	b2.y = b1.y + b2.h + 7;

	SDL_Rect b3;
	b3.w = SCREEN_WIDTH / 2;
	b3.h = 70;
	b3.x = 0 + SCREEN_WIDTH / 4;
	b3.y = b2.y + b3.h + 7;

	SDL_Rect clear;
	clear.w = b1.w + 20;
	clear.h = b1.h + b2.h + b3.h + 36;
	clear.x = b1.x - 10;
	clear.y = b1.y - 10;

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &clear);


	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &b1);

	SDL_SetRenderDrawColor(gRenderer, 255, 0, 170, 255);
	SDL_RenderFillRect(gRenderer, &b2);

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
	SDL_RenderFillRect(gRenderer, &b3);

	

	TTF_SizeText(gFont, "play", &tW, &tH);
	gButtonPlayTextTexture.render(gRenderer, b1.x + (b1.w / 2) - tW/2, b1.y + (b1.h /2 ) -tH/2);

	TTF_SizeText(gFont, "settings", &tW, &tH);
	gButtonSettingsTextTexture.render(gRenderer, b2.x + (b2.w / 2) - tW / 2, b2.y + (b2.h / 2) - tH / 2);

	TTF_SizeText(gFont, "high scores", &tW, &tH);
	gButtonHighScoresTextTexture.render(gRenderer, b3.x + (b3.w / 2) - tW / 2, b3.y + (b3.h / 2) - tH / 2);

	if (buttonSelected == 1)
	{
		gButtonSelectTexture.render(gRenderer, b1.x - 8, b1.y-7);
	}
	else if (buttonSelected == 2)
	{
		gButtonSelectTexture.render(gRenderer, b2.x - 8, b2.y - 7);
	}
	else if (buttonSelected == 3)
	{
		gButtonSelectTexture.render(gRenderer, b3.x - 8, b3.y - 7);
	}
}

void JamesSnake::setupObstacles()
{
	obstacles.clear();
	for (int i = 0; i < 24; i++)
	{
		SDL_Rect k;
		k.w = SEGMENT_WIDTH;
		k.h = SEGMENT_HEIGHT;

		obstacles.push_back(k);
	}

	//UPPER LEFT BLOCKADE
	obstacles[0].x = GAME_FIELD_XPOS;
	obstacles[0].y = GAME_FIELD_YPOS;

		obstacles[1].x = GAME_FIELD_XPOS + SEGMENT_WIDTH;
		obstacles[1].y = GAME_FIELD_YPOS;

		obstacles[2].x = GAME_FIELD_XPOS + SEGMENT_WIDTH*2;
		obstacles[2].y = GAME_FIELD_YPOS;

		obstacles[3].x = GAME_FIELD_XPOS + SEGMENT_WIDTH * 3;
		obstacles[3].y = GAME_FIELD_YPOS;

		obstacles[4].x = GAME_FIELD_XPOS;
		obstacles[4].y = GAME_FIELD_YPOS + SEGMENT_HEIGHT;

		obstacles[5].x = GAME_FIELD_XPOS;
		obstacles[5].y = GAME_FIELD_YPOS + SEGMENT_HEIGHT*2;

		
	//UPPER RIGHT BLOCKADE
	obstacles[6].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH;
	obstacles[6].y = GAME_FIELD_YPOS;

	obstacles[7].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH*2;
	obstacles[7].y = GAME_FIELD_YPOS;

	obstacles[8].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH*3;
	obstacles[8].y = GAME_FIELD_YPOS;

	obstacles[9].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH*4;
	obstacles[9].y = GAME_FIELD_YPOS;

	obstacles[10].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH;
	obstacles[10].y = GAME_FIELD_YPOS+SEGMENT_HEIGHT;

	obstacles[11].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH;
	obstacles[11].y = GAME_FIELD_YPOS + SEGMENT_HEIGHT*2;



	//LOWER RIGHT BLOCKADE
	obstacles[12].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH;
	obstacles[12].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	obstacles[13].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH;
	obstacles[13].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT*2;

	obstacles[14].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH;
	obstacles[14].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT*3;

	obstacles[15].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH*2;
	obstacles[15].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	obstacles[16].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH*3;
	obstacles[16].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	obstacles[17].x = GAME_FIELD_XPOS + GAME_FIELD_WIDTH - SEGMENT_WIDTH*4;
	obstacles[17].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	//LOWER LEFT BLOCKADE
	obstacles[18].x = GAME_FIELD_XPOS;
	obstacles[18].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	obstacles[19].x = GAME_FIELD_XPOS + SEGMENT_WIDTH;
	obstacles[19].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	obstacles[20].x = GAME_FIELD_XPOS + SEGMENT_WIDTH *2;
	obstacles[20].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	obstacles[21].x = GAME_FIELD_XPOS + SEGMENT_WIDTH*3;
	obstacles[21].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT;

	obstacles[22].x = GAME_FIELD_XPOS;
	obstacles[22].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT*2;

	obstacles[23].x = GAME_FIELD_XPOS;
	obstacles[23].y = GAME_FIELD_YPOS + GAME_FIELD_HEIGHT - SEGMENT_HEIGHT*3;
}

void JamesSnake::renderObstacles()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		gObstacleTexture.render(gRenderer, obstacles[i].x, obstacles[i].y);


	}
}

void JamesSnake::checkObstacleCollision()
{
	for (int i = 0; i < obstacles.size(); i++)
	{

		if (checkCollision(segments[0].mCollider, obstacles[i]))
		{
			gameOver = true;

			menuStart = true;
			//mainGameLoop();
		}
	}
}

void JamesSnake::checkBoundaryCollision()
{
	//If the snake collided or went too far to the left or right
	if (segments[0].mPosX + SEGMENT_WIDTH > (GAME_FIELD_WIDTH + GAME_FIELD_XPOS))
	{
		//mainGameLoop();
		segments[0].mPosX = GAME_FIELD_XPOS;
	}

	if (segments[0].mPosX < GAME_FIELD_XPOS)
	{
		segments[0].mPosX = GAME_FIELD_WIDTH;
	}

	//If the dot collided or went too far up or down
	if ((segments[0].mPosY + SEGMENT_HEIGHT >(GAME_FIELD_HEIGHT + GAME_FIELD_YPOS)))
	{
		//mainGameLoop();
		segments[0].mPosY = GAME_FIELD_YPOS;
	}

	if (segments[0].mPosY < GAME_FIELD_YPOS)
	{
		segments[0].mPosY = GAME_FIELD_HEIGHT+SEGMENT_HEIGHT;
	}
}

void JamesSnake::getUserName()
{
	SDL_Rect nameUnderline;
	nameUnderline.w = SCREEN_WIDTH / 2;
	nameUnderline.h = 3;
	nameUnderline.x = SCREEN_WIDTH / 4;
	nameUnderline.y = (SCREEN_HEIGHT / 2) + 10;

	SDL_Rect nameClear;
	nameClear.w = SCREEN_WIDTH / 2;
	nameClear.h = 43;
	nameClear.x = SCREEN_WIDTH / 4;
	nameClear.y = (SCREEN_HEIGHT / 2) - 35;

	cursorBlinkTimer = 0;
	while (!quit)
	{
		SDL_Delay(GAME_STEP_RATE);
		cursorBlinkTimer += 18;
		while (SDL_PollEvent(&e) != 0)
		{

			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.key.type == SDL_KEYDOWN)
			{
				std::string test(SDL_GetKeyName(e.key.keysym.sym));
				if ((test.length() == 1) && (nameBuffer.length() < 22))
				{
					nameBuffer += SDL_GetKeyName(e.key.keysym.sym);

				}
			}

			handleEvent(e);
			SDL_Color textColor = { 255, 255, 0 };
			if (!gNameBufferTexture.loadFromRenderedText(nameBuffer, textColor, gRenderer, gFont))
			{
				printf("Failed to render text texture!\n");

			}
		}

		if (!gettingName)
		{
			break;
		}


		TTF_SizeText(gFont, "enter your name", &tW, &tH);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

		gEnterNameTexture.render(gRenderer, (SCREEN_WIDTH / 2) - (tW / 2), (SCREEN_HEIGHT / 2) - tH * 2);

		//clearing rect
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderFillRect(gRenderer, &nameClear);

		TTF_SizeText(gFont, (char*)nameBuffer.c_str(), &tW, &tH);
		gNameBufferTexture.render(gRenderer, (SCREEN_WIDTH / 2) - (tW / 2), (SCREEN_HEIGHT / 2) - tH * 2 + 45);

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(gRenderer, &nameUnderline);



		//draws blinking cursor
		if (cursorBlinkTimer > 500)
		{
			SDL_RenderDrawLine(gRenderer, nameUnderline.w + (tW / 2), nameUnderline.y - 35, nameUnderline.w + (tW / 2), nameUnderline.y - 7);

			if (cursorBlinkTimer > 1000)
			{
				//SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				//SDL_RenderDrawLine(gRenderer, nameUnderline.w, nameUnderline.y - 35, nameUnderline.w, nameUnderline.y - 7);
				cursorBlinkTimer = 0;
			}
		}



		SDL_RenderPresent(gRenderer);
	}
}

void JamesSnake::mainMenuLoop()
{
	while (!quit)
	{

		while (SDL_PollEvent(&e) != 0)
		{

			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			handleEvent(e);
		}

		if (!menuStart)
		{
			break;
		}
		if (gameOver)
		{
			TTF_SizeText(gFont, "game over", &tW, &tH);
			gGameOverTextTexture.render(gRenderer, (SCREEN_WIDTH / 2) - (tW / 2), (GAME_FIELD_HEIGHT / 2));
		}

		showButtonMenu(buttonSelection);
		SDL_RenderPresent(gRenderer);


	}
}


void JamesSnake::mainGameLoop()
{
	//menuStart = true;

	srand(time(NULL));

	bonusTimer = 0;
	score = 0;
	setGameText();

	//Set field variables
	SDL_Rect field;
	field.w = GAME_FIELD_WIDTH;
	field.h = GAME_FIELD_HEIGHT;

	field.x = GAME_FIELD_XPOS;
	field.y = GAME_FIELD_YPOS;

	//The dot that will be moving around on the screen
	SnakeSegment head;
	head.mPosX = getBlockPos((GAME_FIELD_WIDTH / 2) - (GAME_FIELD_WIDTH / 6));
	head.mPosY = getBlockPos((GAME_FIELD_HEIGHT / 2));

	

	//clear snake tail and add head
	segments.clear();
	segments.push_back(head);
	addSnakeSegment();
	addSnakeSegment();

	
	//set obstacles
	setupObstacles();

	food.w = SEGMENT_WIDTH;
	food.h = SEGMENT_HEIGHT;

	food.x = getBlockPos((GAME_FIELD_WIDTH / 2) + (GAME_FIELD_WIDTH / 6));
	food.y = getBlockPos((GAME_FIELD_HEIGHT / 2));

	bonusFood.w = SEGMENT_WIDTH;
	bonusFood.h = SEGMENT_HEIGHT;
	bonusFood.x = 0;
	bonusFood.y = 0;

	

	////test
	//gObstacleTexture.mHeight = gObstacleTexture.mHeight * scaleFactor;
	//gHeadTexture.mHeight = gHeadTexture.mHeight * scaleFactor;
	//gSegmentTexture.mHeight = gSegmentTexture.mHeight * scaleFactor;
	//gKeyTexture.mHeight = gKeyTexture.mHeight * scaleFactor;

	//gScoreTextTexture.mHeight = gScoreTextTexture.mHeight * scaleFactor;
	//gMapTextTexture.mHeight = gMapTextTexture.mHeight * scaleFactor;
	//gBestTextTexture.mHeight = gBestTextTexture.mHeight * scaleFactor;
	//gBonusTextTexture.mHeight = gBonusTextTexture.mHeight * scaleFactor;

	//gButtonPlayTextTexture.mHeight = gButtonPlayTextTexture.mHeight * scaleFactor;
	//gButtonSettingsTextTexture.mHeight = gButtonSettingsTextTexture.mHeight * scaleFactor;
	//gButtonHighScoresTextTexture.mHeight = gButtonHighScoresTextTexture.mHeight * scaleFactor;



	//gObstacleTexture.mWidth = gObstacleTexture.mWidth * scaleFactor;
	//gHeadTexture.mWidth = gHeadTexture.mWidth * scaleFactor;
	//gSegmentTexture.mWidth = gSegmentTexture.mWidth * scaleFactor;
	//gKeyTexture.mWidth = gKeyTexture.mWidth * scaleFactor;

	//gScoreTextTexture.mWidth = gScoreTextTexture.mWidth * scaleFactor;
	//gMapTextTexture.mWidth = gMapTextTexture.mWidth * scaleFactor;
	//gBestTextTexture.mWidth = gBestTextTexture.mWidth * scaleFactor;
	//gBonusTextTexture.mWidth = gBonusTextTexture.mWidth * scaleFactor;

	//gButtonPlayTextTexture.mWidth = gButtonPlayTextTexture.mWidth * scaleFactor;
	//gButtonSettingsTextTexture.mWidth = gButtonSettingsTextTexture.mWidth * scaleFactor;
	//gButtonHighScoresTextTexture.mWidth = gButtonHighScoresTextTexture.mWidth * scaleFactor;


	SDL_Color textColor = { 255, 255, 255 };
	if (!gEnterNameTexture.loadFromRenderedText("enter your name", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}


	gameOver = false;


	//SDL_FillRect(gSegmentTexture.mTexture, food, SDL_mapRGB(s->format(100, 200, 300));

	//While application is running
	while (!quit)
	{
		

		if (pause)
		{
			while (true)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					handleEvent(e);
				}

				if (!pause)
				{
					break;
				}
			}
		}



		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			handleEvent(e);

		}

		segments[0].move();


		//if the snake collides with food
		if (checkCollision(segments[0].mCollider, food))
		{
			score += 1;
			if (score > bestScore)
			{
				bestScore += 1;
			}
			setGameText();
			addSnakeSegment();
			spawnFood();

			if (score > 0 && score % 5 == 0)
			{
				bonusTimer = 0;
				spawnBonusFood();
			}
		}

		if (checkCollision(segments[0].mCollider, bonusFood))
		{
			bonusFood.x = 0;
			bonusFood.y = 0;
			score += 1;
			if (score > bestScore)
			{
				bestScore += 1;
			}
			setGameText();
			addSnakeSegment();
		}

		for (int i = 1; i < segments.size(); i++)
		{
			if (checkCollision(segments[0].mCollider, segments[i].mCollider))
			{
				gameOver = true;

				menuStart = true;
				
			}

		}

		

		checkObstacleCollision();
		checkBoundaryCollision();


		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render food
	
		SDL_SetRenderDrawColor(gRenderer, 0, 255, 100, 255);
		SDL_RenderFillRect(gRenderer, &food);

		if (bonusFood.x != 0 && bonusTimer < 24)
		{
			SDL_Color textColor = { 0, 0, 0 };
			if (!gBonusTextTexture.loadFromRenderedText(std::to_string(5 - (bonusTimer/5)), textColor, gRenderer, gFont))
			{
				printf("Failed to render text texture!\n");

			}
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
			SDL_RenderFillRect(gRenderer, &bonusFood);

			gBonusTextTexture.render(gRenderer, bonusFood.x+10, bonusFood.y+10);

			bonusTimer += segments[0].moveFactor / 1000;
		}
		
		if(bonusTimer > 24)
		{ 
			bonusTimer = 0;
			bonusFood.x = 0;
			bonusFood.y = 0;

		}

		//print blue square game field
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawRect(gRenderer, &field);


		

		renderObstacles();

		//Update Snake Chain
		updateSnake();

		//Render segments	
		renderSnake();

		//print score, map name, best score
		gScoreTextTexture.render(gRenderer, 40, 25);
		TTF_SizeText(gFont, (char*)mapName.c_str(), &tW, &tH);
		gMapTextTexture.render(gRenderer, (SCREEN_WIDTH/2) - (tW/2), 25);
		gBestTextTexture.render(gRenderer, SCREEN_WIDTH - 175, 25);

		gKeyTexture.render(gRenderer, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - 250);


		//Update screen
		SDL_RenderPresent(gRenderer);

		if (menuStart)
		{
			mainMenuLoop();
		}

		if (gettingName)
		{
			getUserName();
		}

		if (settingsMenu)
		{


			while (true)
			{
				while (SDL_PollEvent(&e) != 0)
				{

					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					handleEvent(e);
				}

				if (!settingsMenu)
				{
					break;
				}
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				//Update screen
				SDL_RenderPresent(gRenderer);

			}
		}

	}




	//SDL_WaitThread(threadID, NULL);

	//Free resources and close SDL
	close();

}