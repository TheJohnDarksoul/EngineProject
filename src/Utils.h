#pragma once

#include <cstdint>
#include <SDL.h>
#include "datastructs.h"

#define PI 3.1415926f
#define TAU (2.f * PI)
#define EPS 1e-9

static class Utils
{
public:
	static float degToRad(float deg);
	static float radToDeg(float rad);
	static float cross2d(Vector2 v1, Vector2 v2);
	static float cross2d(float x0, float x1, float y0, float y1);
	static Vector2 normalize(Vector2 v);
	static float normalizeAngle(float angle);
	/*
	* Calculates and returns the intersection point of two lines.
	* NAN, NAN is returned if the lines do not intersect
	*/
	static Vector2 intersectLines(Vector2 start1, Vector2 end1, Vector2 start2, Vector2 end2);
	static Vector2 intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	/*
	* Rotates a vec2 by an angle given in degrees
	*/
	static Vector2 rotateVec(Vector2 v, float a);
	static Vector2 addVec(Vector2 v1, Vector2 v2);
	static Vector2 subVec(Vector2 v1, Vector2 v2);
	static Vector2 multVec(Vector2 vec, float scalar);
	static bool isOnFront(Vector2 v1, Vector2 v2);

	/*
	* Draws a solid color vertical line to the surface at position x from y1 to y2 inclusive
	* Must be using a 32 bpp format
	*/
	static void drawVertLineColor(SDL_Surface* surface, int x, int y1, int y2, uint32_t color);
	static void drawVertLineColors(SDL_Surface* surface, int x, int y1, int y2, uint32_t topColor, uint32_t midColor, uint32_t bottomColor);
};

