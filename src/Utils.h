#pragma once

#include "datastructs.h"

#define PI 3.1415926f

static class Utils
{
public:
	static float degToRad(float deg);
	static float cross2d(Vector2 v1, Vector2 v2);
	static Vector2 normalize(Vector2 v);
};

