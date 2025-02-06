#include <iostream>
#include <SDL.h>

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cout << "Video failed to init!\n";
		return 1;
	}

	std::cout << "SDL3 is working!\n";

	SDL_Quit();

	return 0;
}