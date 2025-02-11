#pragma once

#include <SDL.h>
#include "datastructs.h"

//Lines that make up the level data
class Segment 
{
private:
	Vector2 start;
	Vector2 end;

	//int frontSectorId;
	//int backSectorId;

public:
	Segment();
	Segment(float startX, float startY, float endX, float endY);
	~Segment();

	Vector2 getStart();
	Vector2 getEnd();
};

//The area enclosed by segments
class Sector 
{
private:
	float floorHeight;
	float ceilingHeight;

	SDL_Texture* floorTexture;
	SDL_Texture* ceilingTexture;

public:
	Sector();
	~Sector();

};

//Makes up the BSP tree, used for all sorts of things including rendering
class Node 
{
private:
	Node* front;
	Node* back;

	Vector2 splitterStart;
	Vector2 splitterEnd;

public:
	Node();
	~Node();

};