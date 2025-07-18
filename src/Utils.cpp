#include "Utils.h"

#include <math.h>
#include <iostream>

void Utils::drawLineLow(SDL_Surface* surface, int x1, int y1, int x2, int y2, uint32_t color)
{
	uint32_t* pixels = (uint32_t*)surface->pixels;

	int dx = x2 - x1;
	int dy = y2 - y1;

	int yi = 1;

	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	int D = 2 * dy - dx;

	int y = y1;

	for (int x = x1; x < x2; ++x)
	{
		pixels[y * surface->w + x] = color;

		if (D > 0)
		{
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else
		{
			D = D + 2 * dy;
		}
	}
}

void Utils::drawLineHigh(SDL_Surface* surface, int x1, int y1, int x2, int y2, uint32_t color)
{
	uint32_t* pixels = (uint32_t*)surface->pixels;

	int dx = x2 - x1;
	int dy = y2 - y1;

	int xi = 1;

	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}

	int D = 2 * dx - dy;

	int x = x1;

	for (int y = y1; y < y2; ++y)
	{
		pixels[y * surface->w + x] = color;

		if (D > 0)
		{
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else
		{
			D = D + 2 * dx;
		}
	}
}

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
	return Vector2{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
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

	if (det == 0.f) //Stop potential divide-by-zero
	{
		det += EPS;
	}

	i.x = cross2d(i.x, x1 - x2, i.y, x3 - x4) / det;
	i.y = cross2d(i.x, y1 - y2, i.y, y3 - y4) / det;

	return i;
}

bool Utils::doSegementsIntersect(Vector2 a, Vector2 b, Vector2 c, Vector2 d)
{
	Vector2 r = subVec(b, a);
	Vector2 s = subVec(d, c);

	float rxs = cross2d(r, s);

	Vector2 cma = subVec(c, a);

	float t = cross2d(cma, s) / rxs;
	float u = cross2d(cma, r) / rxs;

	if (t >= 0.f && t <= 1.f && u >= 0.f && u <= 1.f) 
	{
		return true;
	}

	return false;
}

bool Utils::doRaySegmentIntersect(Vector2 p1, Vector2 p2, Vector2 origin, Vector2 direction)
{
	Vector2 v1 = Utils::subVec(origin, p1);
	Vector2 v2 = Utils::subVec(p2, p1);
	Vector2 v3{ -direction.y, direction.x };

	float dot = v2.x * v3.x + v2.y * v3.y;

	if (dot < EPS) 
	{
		return false;
	}

	float t1 = Utils::cross2d(v2, v1) / dot;
	float t2 = (v1.x * v3.x + v1.y * v3.y) / dot;

	if (t1 >= 0.f && (t2 >= 0.f && t2 <= 1.f)) 
	{
		return true;
	}

	return false;
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

int Utils::isOnSide(Vector2 a, Vector2 b, Vector2 p)
{
	return -(((p.x - a.x) * (b.y - a.y)) - ((p.y - a.y) * (b.x - a.x)));
	//return 0;
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
	if (fabsf(x2 - x1) < .000001f) {
		return y2 - y1;
	}
	return (y2 - y1) / (x2 - x1);
}

void Utils::drawLine(SDL_Surface* surface, int x1, int y1, int x2, int y2, uint32_t color)
{
	x1 = SDL_clamp(x1, 0, surface->w - 1);
	x2 = SDL_clamp(x2, 0, surface->w - 1);

	y1 = SDL_clamp(y1, 0, surface->h - 1);
	y2 = SDL_clamp(y2, 0, surface->h - 1);

	if (labs(y2 - y1) < labs(x2 - x1)) 
	{
		if (x1 > x2) 
		{
			drawLineLow(surface, x2, y2, x1, y1, color);
		}
		else 
		{
			drawLineLow(surface, x1, y1, x2, y2, color);
		}
	}
	else 
	{
		if (y1 > y2) 
		{
			drawLineHigh(surface, x2, y2, x1, y1, color);
		}
		else 
		{
			drawLineHigh(surface, x1, y1, x2, y2, color);
		}
	}
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

uint32_t Utils::SDLcolorToARGB(SDL_Color color)
{
	uint32_t argbcolor = 0;
	argbcolor |= ((uint32_t)color.a << 24);
	argbcolor |= ((uint32_t)color.r << 16);
	argbcolor |= ((uint32_t)color.g << 8);
	argbcolor |= ((uint32_t)color.b);

	return argbcolor;
}
