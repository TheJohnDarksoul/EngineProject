#include "levelcomponents.h"

#include <iostream>
#include <SDL.h>

Segment::Segment() 
{
	//Default values
	start.x = 0.f;
	start.y = 0.f;

	end.x = 0.f;
	end.y = 0.f;

	vec.x = end.x - start.x;
	vec.y = end.y - start.y;
}

Segment::Segment(float startX, float startY, float endX, float endY)
{
	start.x = startX;
	start.y = startY;

	end.x = endX;
	end.y = endY;

	vec.x = end.x - start.x;
	vec.y = end.y - start.y;
}

Segment::Segment(Vector2 start, Vector2 end)
{
	this->start = start;
	this->end = end;

	vec.x = end.x - start.x;
	vec.y = end.y - start.y;
}

Segment::~Segment()
{

}

//Return the starting position of the segment
Vector2 Segment::getStart()
{
	return start;
}

//Return the ending position of the segment
Vector2 Segment::getEnd()
{
	return end;
}

Vector2 Segment::getVector()
{
	return vec;
}

//Renders segments as 2d lines, could be used later for an automap feature
void Segment::render2d(SDL_Renderer* renderer)
{
	SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
}

Sector::Sector()
{
	floorHeight = 0.f;
	ceilingHeight = 0.f;

	floorTexture = nullptr;
	ceilingTexture = nullptr;
}

Sector::~Sector()
{

}

//Returns a non-const pointer to the front node
Node* Node::getFront()
{
	return front;
}

//Returns a non-const pointer to the back node
Node* Node::getBack()
{
	return back;
}

void Node::setFront(Node* node)
{
	front = node;
}

void Node::setBack(Node* node)
{
	back = node;
}

Node::Node()
{
	front = nullptr;
	back = nullptr;

	splitterStart.x = 0.f;
	splitterStart.y = 0.f;
	splitterEnd.x = 0.f;
	splitterEnd.y = 0.f;
}

Node::~Node()
{
	
}