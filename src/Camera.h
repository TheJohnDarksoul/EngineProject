#pragma once

#include<SDL.h>
#include "datastructs.h"

class Line;

//The level is rendered from this object's perspective
class Camera
{
private:
	Vector2 lastPosition;
	Vector2 position;
	float height;

	float angle;
	float fov;
	float vfov;

	uint32_t sector;

	void calcVFov();

public:
	Camera();
	~Camera();

	Vector2 getPosition();
	float getHeight();
	float getAngle();
	float getFov();
	float getFovRad();
	float getVFov();
	uint32_t getSectorNum();

	Vector2 convertCoords(Vector2 pos);
	int screenAngleToX(float angle, int width);

	void setPosition(float x, float y);
	void setHeight(float height);
	void setPosition(float x, float y, float height);
	void setAngle(float angle);
	void setSectorNum(uint32_t sector);

	void move(float x, float y, float h, float dt);
	void rotate(float delta);

	void render2d(SDL_Renderer* renderer);
	void draw2d(SDL_Surface* surface, uint32_t color);
};

