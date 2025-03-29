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

	SDL_SetRenderLogicalPresentation(renderer, 640, 360, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
	//SDL_SetRenderLogicalPresentation(renderer, 640, 360, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

GameWindow::GameWindow(unsigned int w, unsigned int h)
{
	window = SDL_CreateWindow("Engine", w, h, 0);

	if (window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window Creation Error", "Window failed to init", NULL);
	}

	drawSurface = SDL_GetWindowSurface(window);

	//std::cout << SDL_GetWindowSurface(window)->pitch / SDL_GetWindowSurface(window)->w << "\n";

	renderer = SDL_CreateSoftwareRenderer(drawSurface);

	if (renderer == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Creation Error", "Renderer failed to init", window);
	}

	SDL_SetRenderLogicalPresentation(renderer, 640, 360, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
	//SDL_SetRenderLogicalPresentation(renderer, 640, 360, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

//Destructor
GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

//Returns a pointer to the SDL_Window
SDL_Window* GameWindow::getWindow()
{
	return window;
}

//Returns a pointer to the SDL_Renderer
SDL_Renderer* GameWindow::getRenderer()
{
	return renderer;
}

SDL_Surface* GameWindow::getWindowSurface()
{
	return drawSurface;
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
	SDL_UpdateWindowSurface(window);
	SDL_RenderPresent(renderer);
}
