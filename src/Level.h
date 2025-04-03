#pragma once

#include <vector>
#include <string>
#include <queue>

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
	//std::vector<bool> drawnSectors;

	std::queue<Sector*> sectorQueue;

	std::vector<uint16_t> upperPixDrawn;
	std::vector<uint16_t> lowerPixDrawn;

	/*
	* Pushes sector pointer to sector queue
	*/
	void addSectorToQueue(Sector* sec);

public:
	Level();
	~Level();

	/*
	* Sets the upper and lower screen bounds the level can be drawn to at each pixel column
	*/
	void setDrawBounds(SDL_Surface* surface);

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
	void renderSectors(SDL_Renderer* renderer, SDL_Surface* surface, Camera* cam);
};

