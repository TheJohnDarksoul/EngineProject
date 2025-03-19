#pragma once

#include<SDL.h>
#include "datastructs.h"

#define Z_NEAR 0.0001f
#define Z_FAR 1024.f

//The level is rendered from this object's perspective
class Camera
{
private:
	Vector2 position;
	float height;

	float angle;
	float fov;

	int sector;
public:
	Camera();
	~Camera();

	Vector2 getPosition();
	float getHeight();
	float getAngle();
	float getFov();
	float getFovRad();

	Vector2 convertCoords(Vector2 pos);
	int screenAngleToX(float angle, int width);

	void setPosition(float x, float y);
	void setHeight(float height);
	void setPosition(float x, float y, float height);
	void setAngle(float angle);

	void move(float x, float y, float h, float dt);
	void rotate(float delta);

	void render2d(SDL_Renderer* renderer);
};

