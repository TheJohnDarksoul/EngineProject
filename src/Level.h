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
	std::vector<bool> drawnSectors;

	std::queue<Sector*> sectorQueue;

	std::vector<uint16_t> upperPixDrawn;
	std::vector<uint16_t> lowerPixDrawn;

	/*
	* Pushes sector pointer to sector queue
	*/
	void addSectorToQueue(Sector* sec);

	void sortWallsAtSectorNum(unsigned sectorNum, Vector2 cameraPos);

	uint32_t camInSector(Camera* cam);

public:
	Level();
	~Level();

	/*
	* Sets the upper and lower screen bounds the level can be drawn to at each pixel column to default values
	*/
	void setDrawBounds(SDL_Surface* surface);

	/*
	* Prints out relevent sector information for debugging purposes
	*/
	void printSectorInformation();

	/*
	* Reads in level data from a file. Returns 0 on success, 1 on failure.
	* Currently just crashes on failure instead of returning, rewrite this later when you have more time.
	*/
	int loadLevel(std::string filepath);

	void updatePlayerSector(Camera* cam);

	/*
	* Render a 2d representation of the level
	*/
	void render2d(SDL_Renderer* renderer, SDL_Color color);
	void renderMap(SDL_Renderer* renderer, SDL_Surface* surf, Camera* cam);
	void drawMap(SDL_Surface* surface, Camera* cam);
	void render(SDL_Renderer* renderer, SDL_Surface* surface, Camera* cam);
	/*
	* Renders all sectors visible to the camera
	* Must call updatePlayerSector first
	*/
	void renderSectors(SDL_Renderer* renderer, SDL_Surface* surface, Camera* cam);
	void renderSectorsGLM(SDL_Renderer* renderer, SDL_Surface* surface, Camera* cam);
	void renderWall(SDL_Renderer* renderer, SDL_Surface* surface, float x1, float x2, float y1a, float y1b, float y2a, float y2b, SDL_FColor color);
};

