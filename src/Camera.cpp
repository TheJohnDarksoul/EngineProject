#include "Camera.h"

Camera::Camera()
{
	position.x = 0.f;
	position.y = 0.f;
	height = 0.f;
	angle = 0.f;
	fov = 90.f;
}

Camera::~Camera()
{

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
}
