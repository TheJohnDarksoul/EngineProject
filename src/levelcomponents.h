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
public:
	Node* front;
	Node* back;

	Vector2 splitterStart;
	Vector2 splitterEnd;

	Vector2 splitterVec;

	uint32_t segmentId;

public:
	Node* getFront();
	Node* getBack();

	void setFront(Node* node);
	void setBack(Node* node);

	Node();
	~Node();

};