#include "GameWindow.h"

#include <iostream>

//Default constructor
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

//Destructor
GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

//Returns a ppointer to the SDL_Window
SDL_Window* GameWindow::getWindow()
{
	return window;
}

//Returns a pointer to the SDL_Renderer
SDL_Renderer* GameWindow::getRenderer()
{
	return renderer;
}

//Sets the GameWindow title
void GameWindow::setTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

//Clears out the window, should be called before you start rendering each frame
void GameWindow::clearRenderer()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

//Presents your changes to the screen, called at end of frame
void GameWindow::presentRenderer()
{
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}
