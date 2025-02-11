#include "GameWindow.h"

#include <iostream>

GameWindow::GameWindow()
{
	window = SDL_CreateWindow("Engine", 640, 360, 0);

	if (window == nullptr)
	{
		std::cout << "Window failed to init!\n";
	}

	drawSurface = SDL_GetWindowSurface(window);

	renderer = SDL_CreateSoftwareRenderer(drawSurface);
	//renderer = SDL_CreateRenderer(window, NULL);

	if (renderer == nullptr)
	{
		std::cout << "Renderer failed to init!\n" << SDL_GetError() << "\n";
	}
}

GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

SDL_Window* GameWindow::getWindow()
{
	return window;
}

SDL_Renderer* GameWindow::getRenderer()
{
	return renderer;
}

void GameWindow::render()
{
	SDL_SetRenderDrawColor(renderer, 0xb2, 0xb2, 0xff, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}
