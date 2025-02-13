#include "GameWindow.h"

#include <iostream>

//Default constructor
GameWindow::GameWindow()
{
	window = SDL_CreateWindow("Engine", 640, 360, 0);

	if (window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window Creation Error", "Window failed to init", NULL);
	}

	drawSurface = SDL_GetWindowSurface(window);

	renderer = SDL_CreateSoftwareRenderer(drawSurface);

	if (renderer == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Creation Error", "Renderer failed to init", window);
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
