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

float Utils::normalizeAngle(float angle)
{
	return angle - (TAU * floorf(angle + PI / TAU));
}

Vector2 Utils::intersectLines(Vector2 a0, Vector2 a1, Vector2 b0, Vector2 b1)
{
	float a = a0.x - a1.x;
	float b = b0.y - b1.y;
	float c = a0.y - a1.y;
	float d = b0.x - b1.x;

	float denom = a * b - c * d;

	if (fabsf(denom) < EPS) 
	{
		return Vector2{NAN, NAN};
	}

	a = a0.x - b0.x;
	b = b0.y - b1.y;
	c = a0.y - b0.y;
	d = b0.x - b1.x;

	float t = (a * b - c * d) / denom;

	a = a0.x - b0.x;
	b = a0.y - a1.y;
	c = a0.y - b0.y;
	d = a0.x - a1.x;
	

	float u = (a * b - c * d) / denom;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) 
	{
		return Vector2{ a0.x + (t * (a1.x - a0.x)), a0.y + (t * (a1.y - a0.y)) };
	}

	return Vector2{ NAN, NAN };
}

Vector2 Utils::rotateVec(Vector2 v, float a)
{
	Vector2 temp;
	temp.x = (v.x * cosf(a) - (v.y * sinf(a)));
	temp.y = (v.x * sinf(a) + (v.y * cosf(a)));
	return temp;
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
