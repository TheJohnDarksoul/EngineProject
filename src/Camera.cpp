#include "Camera.h"

#include "Utils.h"
#include <math.h>

Camera::Camera()
{
	position.x = 0.f;
	position.y = 0.f;
	height = 0.f;
	angle = 0.f;
	fov = 90.f;
	sector = 0;
}

Camera::~Camera()
{

}

Vector2 Camera::getPosition()
{
	return position;
}

float Camera::getAngle()
{
	return angle;
}

//Sets the camera position to the passed x y values
void Camera::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

//Sets the camera height to the passed value
void Camera::setHeight(float height)
{
	this->height = height;
}

//Sets the camera position to the passes x y values and sets height to the passed value
void Camera::setPosition(float x, float y, float height)
{
	setPosition(x, y);
	setHeight(height);
}

//Sets the camera's rotation to the passed value
void Camera::setAngle(float angle)
{
	this->angle = angle;
}

//Should not be used ingame, only for testing
void Camera::move(float x, float y, float h, float dt)
{
	position.x += x * dt;
	position.y += y * dt;
	height += h * dt;
}

void Camera::rotate(float delta)
{
	angle += delta;
	if (angle > 360.f) 
	{
		angle -= 360.f;
	}
	else if (angle < 0.f) 
	{
		angle += 360.f;
	}
}

//For use in testing, don't use in game
void Camera::render2d(SDL_Renderer* renderer)
{
	//Fill in
	SDL_FRect rect;
	rect.x = position.x - 5;
	rect.y = position.y - 5;
	rect.h = 10.f;
	rect.w = 10.f;

	SDL_SetRenderDrawColor(renderer, 0xff, 0xb2, 0xb2, 0xff);

	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0xb2, 0xff, 0xb2, 0xff);

	//Camera fov visualization
	SDL_RenderLine(renderer, position.x, position.y, position.x + 50 * cosf(Utils::degToRad(angle + 45)), 
		position.y + 50 * sinf(Utils::degToRad(angle + fov / 2)));
	SDL_RenderLine(renderer, position.x, position.y, position.x + 50 * cosf(Utils::degToRad(angle - 45)),
		position.y + 50 * sinf(Utils::degToRad(angle - fov / 2)));
}
