#pragma once

#include <vector>
#include <string>

#include "levelcomponents.h"

enum fileReadStates {READ_SECTORS, READ_LINES};

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
	*/
	int loadLevel(std::string filepath);

	void drawWalls(SDL_Surface* surface, Camera* cam);
};

