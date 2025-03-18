#include "Utils.h"

#include <math.h>
#include <iostream>

float Utils::degToRad(float deg)
{
	return deg * (PI / 180);
}

float Utils::cross2d(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.y - v2.x * v1.y	;
}

Vector2 Utils::normalize(Vector2 v)
{
	float len = powf(v.x * v.x + v.y * v.y, 0.5f);
	Vector2 norm{ v.x / len, v.y / len };
	return norm;
}

Vector2 Utils::addVec(Vector2 v1, Vector2 v2)
{
	Vector2 sum;
	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	return sum;
}

Vector2 Utils::subVec(Vector2 v1, Vector2 v2)
{
	Vector2 diff;
	diff.x = v1.x - v2.x;
	diff.y = v1.y - v2.y;
	return diff;
}

Vector2 Utils::multVec(Vector2 vec, float scalar)
{
	Vector2 product;
	product.x = vec.x * scalar;
	product.y = vec.y * scalar;
	return product;
}

bool Utils::isOnFront(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.y < v2.x * v1.y;
}

bool Utils::floatEquals(float a, float b, float epsilon)
{
	if (fabsf(a) < fabsf(b)) 
	{
		return fabsf(a - b) <= fabsf(b);
	}

	return fabsf(a - b) <= fabsf(a) * epsilon;
}

bool Utils::floatGreaterThan(float a, float b, float epsilon)
{
	if (fabsf(a) < fabsf(b)) 
	{
		return (a - b) > fabsf(b);
	}

	return (a - b) > (fabsf(a) * epsilon);
}

void Utils::drawVertLineColor(SDL_Surface* surface, int x, int y1, int y2, uint32_t color)
{
	if (surface != nullptr)
	{
		unsigned int i;
		for (i = y1; i <= y2; ++i)
		{
			uint32_t* pixels = (uint32_t*)surface->pixels;
			pixels[i * surface->w + x] = color;
		}
	}
}
