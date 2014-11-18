
//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "time.h"
#include <SDL_thread.h>



#include "JamesSnake.h"


int main(int argc, char* args[])
{
	JamesSnake game = JamesSnake::getInstance();
		game.start();
		game.mainGameLoop();

	return 0;
}