#include "levelcomponents.h"

#include <iostream>
#include <SDL.h>

#include "Utils.h"

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

void Segment::setPosition(float x1, float y1, float x2, float y2)
{
	start.x = x1;
	start.y = y2;
	end.x = x2;
	end.y = y2;
}

void Segment::setPosition(Vector2 p1, Vector2 p2)
{
	start = p1;
	end = p2;
}

void Segment::setVector(Vector2 vec)
{
	this->vec = vec;
}

//Renders segments as 2d lines, could be used later for an automap feature
void Segment::render2d(SDL_Renderer* renderer, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);

	//Draw line facing
	Vector2 norm = Utils::normalize(Vector2{ -vec.y, vec.x });

	Vector2 point1;

	point1.x = start.x + end.x;
	point1.y = start.y + end.y;

	point1 = Utils::multVec(point1, 0.5);

	Vector2 point2;

	point2 = Utils::addVec(point1, Utils::multVec(norm, 5));

	SDL_RenderLine(renderer, point1.x, point1.y, point2.x, point2.y);
}

void Segment::renderSegments(SDL_Renderer* renderer, std::vector<Segment>* segments, SDL_Color color)
{
	for (unsigned int i = 0; i < segments->size(); ++i) 
	{
		segments->at(i).render2d(renderer, color);
	}
	for (unsigned int i = 0; i < segments->size(); ++i) 
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_FRect temp;
		temp.x = segments->at(i).start.x - 2;
		temp.y = segments->at(i).start.y - 2;
		temp.w = 5;
		temp.h = 5;

		SDL_RenderRect(renderer, &temp);

		temp.x = segments->at(i).end.x - 2;
		temp.y = segments->at(i).end.y - 2;

		SDL_RenderRect(renderer, &temp);
	}
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
	//Dummy values, will be overwritten in node builder
	front = nullptr;
	back = nullptr;

	splitterStart.x = 0.f;
	splitterStart.y = 0.f;
	splitterEnd.x = 0.f;
	splitterEnd.y = 0.f;

	splitterVec.x = 0.f;
	splitterVec.y = 0.f;

	segmentId = UINT32_MAX;
}

Node::~Node()
{
	
}