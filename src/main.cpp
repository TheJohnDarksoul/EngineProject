#include <iostream>
#include <SDL.h>

#include "GameWindow.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cout << "Video failed to init!\n";
		return 1;
	}

	GameWindow window;

	while (1) 
	{
		window.render();
	}

	SDL_Quit();

	return 0;
}