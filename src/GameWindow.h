#pragma once

#include <SDL.h>

class GameWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* drawSurface;

public:
	GameWindow();
	GameWindow(unsigned int w, unsigned int h);
	~GameWindow();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	void setTitle(const char* title);

	void clearRenderer();
	void presentRenderer();

};

