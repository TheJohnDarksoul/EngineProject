#include "Utils.h"

#include <math.h>

float Utils::degToRad(float deg)
{
	return deg * (PI / 180);
}

float Utils::cross2d(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

Vector2 Utils::normalize(Vector2 v)
{
	float len = powf(v.x * v.x + v.y * v.y, 0.5f);
	Vector2 norm{ v.x / len, v.y / len };
	return norm;
}
