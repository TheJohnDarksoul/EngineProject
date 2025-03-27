#include "Utils.h"

#include <math.h>
#include <iostream>

float Utils::degToRad(float deg)
{
	return deg * (PI / 180);
}

float Utils::radToDeg(float rad)
{
	return rad * (180 / PI);
}

float Utils::cross2d(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.y - v2.x * v1.y	;
}

float Utils::cross2d(float x0, float x1, float y0, float y1)
{
	return x0 * y1 - x1 * y0;
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

Vector2 Utils::intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	//return Vector2{ 
	//	cross2d(cross2d(x1, y1, x2, y2), (x1)-(x2), cross2d(x3, y3, x4, y4), (x3)-(x4)) / cross2d((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)),
	//	cross2d(cross2d(x1, y1, x2, y2), (y1)-(y2), cross2d(x3, y3, x4, y4), (y3)-(y4)) / cross2d((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) };
	Vector2 i;

	i.x = cross2d(x1, y1, x2, y2);
	i.y = cross2d(x3, y3, x4, y4);
	float det = cross2d(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	i.x = cross2d(i.x, x1 - x2, i.y, x3 - x4) / det;
	i.y = cross2d(i.x, y1 - y2, i.y, y3 - y4) / det;

	return i;
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

/*
* Draws a vertical line at x position between y1 and y2. Colors are ARGB.
*/
void Utils::drawVertLineColors(SDL_Surface* surface, int x, int y1, int y2, uint32_t topColor, uint32_t midColor, uint32_t bottomColor)
{
	if (surface != nullptr) 
	{
		y1 = SDL_clamp(y1, 0, surface->h - 1);
		y2 = SDL_clamp(y2, 0, surface->h - 1);

		if (y1 > y2) 
		{
			int temp = y1;
			y1 = y2;
			y2 = temp;
		}

		uint32_t* pixels = (uint32_t*)surface->pixels;
		uint32_t width = surface->w;

		if (y2 == y1) //Draws a point
		{
			pixels[y1 * width + x] = midColor;
		}
		else if (y2 > y1) 
		{
			pixels[y1 * width + x] = topColor;

			for (unsigned y = y1 + 1; y < y2; ++y) 
			{
				pixels[y * width + x] = midColor;
			}
			pixels[y2 * width + x] = bottomColor;
		}
	}
}
