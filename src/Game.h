#pragma once

#include <iostream>
#include <SDL.h>


class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isOpen;

public:
	Game();
	~Game();

	bool getIsOpen();

};