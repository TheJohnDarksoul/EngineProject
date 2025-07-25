#pragma once

#include <cstdint>
#include <SDL.h>
#include <vector>
#include "datastructs.h"

#define PI 3.1415926f
#define TAU (2.f * PI)
#define EPS 1e-9

static class Utils
{
private:
	static void drawLineLow(SDL_Surface* surface, int x1, int y1, int x2, int y2, uint32_t color);
	static void drawLineHigh(SDL_Surface* surface, int x1, int y1, int x2, int y2, uint32_t color);
public:
	//Math utils

	static float degToRad(float deg);
	static float radToDeg(float rad);
	static float cross2d(Vector2 v1, Vector2 v2);
	static float cross2d(float x0, float x1, float y0, float y1);
	static Vector2 normalize(Vector2 v);
	static float normalizeAngle(float angle);
	static float diagonalDistance(float x1, float y1, float x2, float y2);
	static Vector2 midpt(Vector2 p1, Vector2 p2);

	/*
	* Returns the distance between two points squared
	*/
	static float distanceSquared(Vector2 p1, Vector2 p2);

	/*
	* Returns the distance between two points
	*/
	static float distance(Vector2 p1, Vector2 p2);

	/*
	* Calculates and returns the intersection between two lines
	*/
	static Vector2 intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	static bool doSegementsIntersect(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
	static bool doRaySegmentIntersect(Vector2 p1, Vector2 p2, Vector2 origin, Vector2 direction);

	/*
	* Rotates a vec2 by an angle given in radians
	*/
	static Vector2 rotateVec(Vector2 v, float a);
	static Vector2 rotateVecAroundPoint(Vector2 v, Vector2 p, float a);
	static Vector2 addVec(Vector2 v1, Vector2 v2);
	static Vector2 subVec(Vector2 v1, Vector2 v2);
	static Vector2 multVec(Vector2 vec, float scalar);

	static float lerp(float start, float end, float t);

	static bool isOnFront(Vector2 v1, Vector2 v2);

	/*
	* Returns -1 if p is on the right of a->b, 0 if on, and 1 if on the left
	*/
	static int isOnSide(Vector2 a, Vector2 b, Vector2 p);
	static void clipBehindCamera(float* ax, float* ay, float bx, float by);

	static void calcLineStep(float x1, float y1, float x2, float y2, int* x, int* y);
	static float calcLineSlope(float x1, float y1, float x2, float y2);

	//Drawing utils

	/*
	* Software rendering of arbitrary lines. Might use in automap feature.
	*/
	static void drawLine(SDL_Surface* surface, int x1, int y1, int x2, int y2, uint32_t color);

	/*
	* Draws a solid color vertical line to the surface at position x from y1 to y2 inclusive
	* Must be using a 32 bpp format
	*/
	static void drawVertLineColor(SDL_Surface* surface, int x, int y1, int y2, uint32_t color);
	static void drawVertLineColors(SDL_Surface* surface, int x, int y1, int y2, uint32_t topColor, uint32_t midColor, uint32_t bottomColor);

	//Misc Utils

	/*
	* Converts SDL_Color to an unsigned 32bit int in ARGB format
	* This is the format used when directly writing to the pixel buffer in an SDL_Surface
	*/
	static uint32_t SDLcolorToARGB(SDL_Color color);
};

