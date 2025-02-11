#include "levelcomponents.h"

#include <iostream>

Segment::Segment() 
{
	//Default values
	start.x = 0.f;
	start.y = 0.f;

	end.x = 0.f;
	end.y = 0.f;
}

Segment::Segment(float startX, float startY, float endX, float endY)
{
	start.x = startX;
	start.y = startY;

	end.x = endX;
	end.y = endY;
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
