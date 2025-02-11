#pragma once

#include "datastructs.h"

class Segment 
{
private:
	Vector2 start;
	Vector2 end;

public:
	Segment();
	Segment(float startX, float startY, float endX, float endY);
	~Segment();

	Vector2 getStart();
	Vector2 getEnd();
};