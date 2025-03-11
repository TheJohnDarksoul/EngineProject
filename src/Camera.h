#pragma once

#include<SDL.h>
#include "datastructs.h"

//The level is rendered from this object's perspective
class Camera
{
private:
	Vector2 position;
	float height;
	float angle;
	float fov;
public:
	Camera();
	~Camera();

	Vector2 getPosition();
	float getAngle();

	void setPosition(float x, float y);
	void setHeight(float height);
	void setPosition(float x, float y, float height);
	void setAngle(float angle);

	void move(float x, float y, float h, float dt);
	void rotate(float delta);

	void render2d(SDL_Renderer* renderer);
};

