#include "levelcomponents.h"

#include <iostream>
#include <SDL.h>

#include "Utils.h"

Sector::Sector()
{
	id = 0;

	floorHeight = 0.f;
	ceilingHeight = 0.f;

	numWalls = 0;
}

Sector::Sector(uint32_t id, float fh, float ch, std::vector<uint32_t>* iWalls)
{
	this->id = id;
	floorHeight = fh;
	ceilingHeight = ch;
	numWalls = iWalls->size();

	for (uint32_t i = 0; i < numWalls; ++i) 
	{
		wallindices.push_back(iWalls->at(i));
	}
}

Sector::~Sector()
{

}

uint32_t Sector::getNumWalls()
{
	return numWalls;
}

uint32_t Sector::getID()
{
	return id;
}

const std::vector<uint32_t>* Sector::getWallIndices()
{
	return &wallindices;
}

float Sector::getFloorHeight()
{
	return floorHeight;
}

float Sector::getCeilingHeight()
{
	return ceilingHeight;
}

void Sector::setFloorHeight(float val)
{
	floorHeight = val;
}

void Sector::setCeilingHeight(float val)
{
	ceilingHeight = val;
}

void Sector::swapWallIndexPositions(unsigned p1, unsigned p2)
{
	uint32_t temp = wallindices.at(p1);
	wallindices.at(p1) = wallindices.at(p2);
	wallindices.at(p2) = temp;
}

Line::Line()
{
	start = Vector2{ 0, 0 };
	end = start;
	portal = 0;

	this->color.r = rand() % 256;
	this->color.g = rand() % 256;
	this->color.b = rand() % 256;
	this->color.a = 255;
}

Line::Line(Vector2 start, Vector2 end, int portal)
{
	this->start = start;
	this->end = end;
	this->portal = portal;

	this->color.r = rand() % 256;
	this->color.g = rand() % 256;
	this->color.b = rand() % 256;
	this->color.a = 255;
}

Line::~Line()
{

}

void Line::printPositions()
{
	std::cout << "x1: " << start.x << " y1: " << start.y << " x2: " << end.x << " y2: " << end.y << "\n";
}

Vector2 Line::getStart()
{
	return start;
}

Vector2 Line::getEnd()
{
	return end;
}

int Line::getPortalNum()
{
	return portal;
}

SDL_Color Line::getColor()
{
	return this->color;
}

SDL_FColor Line::getFcolor()
{
	SDL_FColor temp;
	temp.r = color.r / 255.f;
	temp.g = color.g / 255.f;
	temp.b = color.b / 255.f;
	temp.a = 1.0f;

	return temp;
}

void Line::render2d(SDL_Renderer* renderer, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);

	Vector2 vec;

	vec.x = end.x - start.x;
	vec.y = end.y - start.y;

	Vector2 norm = Utils::normalize(Vector2{ -vec.y, vec.x });

	Vector2 point1;

	point1.x = start.x + end.x;
	point1.y = start.y + end.y;

	point1 = Utils::multVec(point1, 0.5);

	Vector2 point2;

	point2 = Utils::addVec(point1, Utils::multVec(norm, 5));

	SDL_RenderLine(renderer, point1.x, point1.y, point2.x, point2.y);
}