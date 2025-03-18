#pragma once

#include <cstdint>
#include <SDL.h>
#include "datastructs.h"

#define PI 3.1415926f
#define EPS 1e-9

static class Utils
{
public:
	static float degToRad(float deg);
	static float cross2d(Vector2 v1, Vector2 v2);
	static Vector2 normalize(Vector2 v);
	static Vector2 addVec(Vector2 v1, Vector2 v2);
	static Vector2 subVec(Vector2 v1, Vector2 v2);
	static Vector2 multVec(Vector2 vec, float scalar);
	static bool isOnFront(Vector2 v1, Vector2 v2);
	static bool floatEquals(float a, float b, float epsilon);
	static bool floatGreaterThan(float a, float b, float epsilon);

	/*
	* Draws a solid color vertical line to the surface at position x from y1 to y2 inclusive
	* Must be using a 32 bpp format
	*/
	static void drawVertLineColor(SDL_Surface* surface, int x, int y1, int y2, uint32_t color);
};

