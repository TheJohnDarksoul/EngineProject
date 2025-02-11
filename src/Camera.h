#pragma once

#include "datastructs.h"

class Camera
{
private:
	Vector2 position;
	float angle;
public:
	Camera();
	~Camera();

	void setPosition(float x, float y);
	void setHeight(float height);
	void setPosition(float x, float y, float height);
	void setAngle(float angle);
};

