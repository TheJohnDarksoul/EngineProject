#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>
#include "datastructs.h"

//The area enclosed by lines
class Sector 
{
private:
	uint32_t id;

	float floorHeight;
	float ceilingHeight;

	std::vector<uint32_t> wallindices;
	uint32_t numWalls;

	//SDL_Texture* floorTexture;
	//SDL_Texture* ceilingTexture;

public:
	Sector();
	Sector(uint32_t id, float fh, float ch, std::vector<uint32_t>* iWalls);
	~Sector();

	uint32_t getNumWalls();
	uint32_t getID();
	const std::vector<uint32_t>* getWallIndices();

	float getFloorHeight();
	float getCeilingHeight();

	void setFloorHeight(float val);
	void setCeilingHeight(float val);

	void swapWallIndexPositions(unsigned p1, unsigned p2);
};

class Line 
{
private:
	Vector2 start;
	Vector2 end;

	int portal;
	SDL_Color color;

	//SDL_Texture* texture;
public:
	Line();
	Line(Vector2 start, Vector2 end, int portal);
	~Line();

	void printPositions();

	Vector2 getStart();
	Vector2 getEnd();

	int getPortalNum();

	SDL_Color getColor();
	SDL_FColor getFcolor();

	void render2d(SDL_Renderer* renderer, SDL_Color color);
};