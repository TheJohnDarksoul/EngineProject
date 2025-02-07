#include "Game.h"

Game::Game():isOpen(true)
{
	window = SDL_CreateWindow("Engine", 640, 360, 0);

	if (window == nullptr) 
	{
		std::cout << "Window failed to init!\n";
		isOpen = false;
	}

	renderer = SDL_CreateRenderer(window, NULL);

	if (renderer == nullptr) 
	{
		std::cout << "Renderer failed to init!\n";
		isOpen = false;
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Game::getIsOpen()
{
	return isOpen;
}
