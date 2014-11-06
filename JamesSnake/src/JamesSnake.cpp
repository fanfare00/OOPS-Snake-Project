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
		gSegmentTexture.gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gSegmentTexture.gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gSegmentTexture.gRenderer = SDL_CreateRenderer(gSegmentTexture.gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gSegmentTexture.gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gSegmentTexture.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
	if (!gSegmentTexture.loadFromFile("dot.bmp"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Open the font
	gTextTexture.gFont = TTF_OpenFont("lazy.ttf", 28);
	if (gTextTexture.gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{

		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor))
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
	SDL_DestroyRenderer(gSegmentTexture.gRenderer);
	SDL_DestroyWindow(gSegmentTexture.gWindow);
	gSegmentTexture.gWindow = NULL;
	gSegmentTexture.gRenderer = NULL;

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
		gSegmentTexture.render(segments[i].mPosX, segments[i].mPosY);
		
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
		SDL_SetRenderDrawColor(gSegmentTexture.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gSegmentTexture.gRenderer);

		//Render food
		SDL_SetRenderDrawColor(gSegmentTexture.gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(gSegmentTexture.gRenderer, &food);
		SDL_RenderDrawRect(gSegmentTexture.gRenderer, &field);

		//Update Snake Chain
		updateSnake();

		//Render segments	
		renderSnake();

		gTextTexture.render(10,10);

		//Update screen
		SDL_RenderPresent(gSegmentTexture.gRenderer);


		
		
	}



	//SDL_WaitThread(threadID, NULL);

	//Free resources and close SDL
	close();

}