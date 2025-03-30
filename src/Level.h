#pragma once

#include <vector>
#include <string>

#include "levelcomponents.h"

enum fileReadStates {READ_SECTORS, READ_LINES, READ_PLAYER};

class Camera;

class Level
{
private:
	//Vector of sectors
	std::vector<Sector> sectors;
	//Vector of lines
	std::vector<Line> lines;

	//Keeps track of which sectors we have drawn. Allocate on level load.
	std::vector<bool> drawnSectors;

public:
	Level();
	~Level();

	/*
	* Reads in level data from a file. Returns 0 on success, 1 on failure.
	* Currently just crashes on failure instead of returning, rewrite this later when you have more time.
	*/
	int loadLevel(std::string filepath);

	/*
	* Render a 2d representation of the level
	*/
	void render2d(SDL_Renderer* renderer, SDL_Color color);
	void render(SDL_Renderer* renderer, SDL_Surface* surface, Camera* cam);
};

