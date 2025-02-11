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
	~GameWindow();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	void render();

};

