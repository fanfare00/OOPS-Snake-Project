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
	if (!gSegmentTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("SlimJoe.ttf", 20);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{

		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, gRenderer, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void JamesSnake::close()
{
	//Free loaded images
	gTextTexture.free();

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



void JamesSnake::handleEvent(SDL_Event& e)
{
	
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (segments[0].mDirection != SNAKE_DIRECTION_DOWN)
			{
				segments[0].mDirection = SNAKE_DIRECTION_UP;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();
	
			}
			break;

		case SDLK_DOWN:
			if (segments[0].mDirection != SNAKE_DIRECTION_UP)
			{
				segments[0].mDirection = SNAKE_DIRECTION_DOWN;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();

			}
			break;

		case SDLK_LEFT:
			if (segments[0].mDirection != SNAKE_DIRECTION_RIGHT)
			{
				segments[0].mDirection = SNAKE_DIRECTION_LEFT;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();

			}

			break;

		case SDLK_RIGHT:
			if (segments[0].mDirection != SNAKE_DIRECTION_LEFT)
			{
				segments[0].mDirection = SNAKE_DIRECTION_RIGHT;
				segments[0].mPosXPrev = segments[0].mPosX;
				segments[0].mPosYPrev = segments[0].mPosY;
				segments[0].moveFactor = 1000;
				//Update Snake Chain
				updateSnake();

				//Render segments	
				renderSnake();

			}
			break;

		case SDLK_p:
			if (!pause)
			{
				pause = true;
				printf("pause");
			}
			else
			{
				pause = false;
				printf("NOT pause");
			}
			break;

		case SDLK_r:
			
			mainGameLoop();
			break;
		}
	}

}

void JamesSnake::spawnFood()
{	

	//Set the food
	food.x = getBlockPos(((rand() % 10) * ((GAME_FIELD_WIDTH+SEGMENT_WIDTH) / 10)));
	food.y = SEGMENT_HEIGHT + getBlockPos(((rand() % 10) * ((GAME_FIELD_HEIGHT + SEGMENT_HEIGHT) / 10)));
	printf("X: %i \n", food.x);
	printf("Y: %i \n", food.y);

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

	for (int i = 0; i < segments.size(); i++)
	{
		//Show the dot
		gSegmentTexture.render(gRenderer, segments[i].mPosX, segments[i].mPosY);
		
	}
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


void JamesSnake::mainGameLoop()
{
	srand(time(NULL));

	//Set field variables
	SDL_Rect field;
	field.w = GAME_FIELD_WIDTH;
	field.h = GAME_FIELD_HEIGHT;

	field.x = GAME_FIELD_XPOS;
	field.y = GAME_FIELD_YPOS;

	//The dot that will be moving around on the screen
	SnakeSegment head;
	head.mPosX = getBlockPos((SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 6));
	head.mPosY = getBlockPos((SCREEN_HEIGHT / 2) - 40);

	//clear snake tail and add head
	segments.clear();
	segments.push_back(head);


	food.w = SEGMENT_WIDTH;
	food.h = SEGMENT_HEIGHT;

	food.x = getBlockPos((SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 6));
	food.y = getBlockPos((SCREEN_HEIGHT / 2) - 40);;



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
			addSnakeSegment();
			spawnFood();
		}

		//If the snake collided or went too far to the left or right
		if ((segments[0].mPosX < GAME_FIELD_XPOS) || (segments[0].mPosX + SEGMENT_WIDTH >(GAME_FIELD_WIDTH + GAME_FIELD_XPOS)))
		{
			mainGameLoop();
		}

		//If the dot collided or went too far up or down
		if ((segments[0].mPosY < GAME_FIELD_YPOS) || (segments[0].mPosY + SEGMENT_HEIGHT >(GAME_FIELD_HEIGHT + GAME_FIELD_YPOS)))
		{
			mainGameLoop();
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render food
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(gRenderer, &food);
		SDL_RenderDrawRect(gRenderer, &field);

		//Update Snake Chain
		updateSnake();

		//Render segments	
		renderSnake();

		gTextTexture.render(gRenderer, 10,10);

		//Update screen
		SDL_RenderPresent(gRenderer);




	}



	//SDL_WaitThread(threadID, NULL);

	//Free resources and close SDL
	close();

}