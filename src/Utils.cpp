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
	return v1.x * v2.y - v2.x * v1.y;
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

float Utils::diagonalDistance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return SDL_max(fabsf(dx), fabsf(dy));
}

Vector2 Utils::midpt(Vector2 p1, Vector2 p2)
{
	return Vector2{(p1.x + p2.x) / 2, (p1.y - p2.y) / 2};
}

float Utils::distanceSquared(Vector2 p1, Vector2 p2)
{
	return ((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y));
}

float Utils::distance(Vector2 p1, Vector2 p2)
{
	return powf(distanceSquared(p1, p2), 0.5f);
}

Vector2 Utils::intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
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

float Utils::lerp(float start, float end, float t)
{
	return start * (1.f - t) + end * t;
}

bool Utils::isOnFront(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.y < v2.x * v1.y;
}

void Utils::clipBehindCamera(float* ax, float* ay, float bx, float by)
{
	float px1 = 1;
	float py1 = 1;
	float px2 = 200;
	float py2 = 1;

	float a = cross2d(px1 - px2, py1 - py2, *ax - px2, *ay - py2);
	float b = cross2d(py1 - py2, px1 - px2, *ay - by, *ax - bx);

	float t = a / b;

	*ax = *ax - (t * (bx - *ax));
	*ay = *ay - (t * (by - *ay));
}

void Utils::calcLineStep(float x1, float y1, float x2, float y2, int* x, int* y)
{
	*y = y2 - y1;
	*x = x2 - x1;
}

float Utils::calcLineSlope(float x1, float y1, float x2, float y2)
{
	return (y2 - y1) / (x2 - x1);
}

void Utils::drawVertLineColor(SDL_Surface* surface, int x, int y1, int y2, uint32_t color)
{
	if (surface != nullptr)
	{
		unsigned int i;
		for (i = y1; i < y2; ++i)
		{
			uint32_t* pixels = (uint32_t*)surface->pixels;
			pixels[i * surface->w + x] = color;
		}
	}
}

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
