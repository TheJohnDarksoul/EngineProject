#include <iostream>
#include <SDL.h>

#include "Game.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cout << "Video failed to init!\n";
		return 1;
	}

	Game game;

	while (game.getIsOpen()) 
	{

	}

	SDL_Quit();

	return 0;
}