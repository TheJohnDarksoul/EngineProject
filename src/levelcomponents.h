#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>
#include "datastructs.h"

//Lines that make up the level data
class Segment 
{
private:
	Vector2 start;
	Vector2 end;

	Vector2 vec;

	//int frontSectorId;
	//int backSectorId;

public:
	Segment();
	Segment(float startX, float startY, float endX, float endY);
	Segment(Vector2 start, Vector2 end);
	~Segment();

	Vector2 getStart();
	Vector2 getEnd();
	Vector2 getVector();

	void setPosition(float x1, float y1, float x2, float y2);
	void setPosition(Vector2 p1, Vector2 p2);
	void setVector(Vector2 vec);

	void render2d(SDL_Renderer* renderer, SDL_Color color);
	static void renderSegments(SDL_Renderer* renderer, std::vector<Segment>* segments, SDL_Color color);
};

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
	const std::vector<uint32_t>* getWallIndices();

	float getFloorHeight();
	float getCeilingHeight();

	void setFloorHeight(float val);
	void setCeilingHeight(float val);

};

class Line 
{
private:
	Vector2 start;
	Vector2 end;

	int portal;
public:
	Line();
	Line(Vector2 start, Vector2 end, int portal);
	~Line();

	void printPositions();

	Vector2 getStart();
	Vector2 getEnd();

	int getPortalNum();

	void render2d(SDL_Renderer* renderer, SDL_Color color);
};