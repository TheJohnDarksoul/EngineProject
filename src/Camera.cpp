#include "Camera.h"

#include "Utils.h"
#include <math.h>
#include <iostream>
#include "levelcomponents.h"

void Camera::calcVFov()
{
	vfov = 2 * atanf(tanf(fov / 2) *  (1 / (16.f / 9.f)));
}

Camera::Camera()
{
	position.x = 0.f;
	position.y = 0.f;
	lastPosition.x = position.x;
	lastPosition.y = position.y;
	height = 15.f;
	angle = 0.f;
	fov = 180;//90;//Utils::degToRad(90.f);
	vfov = 0;
	calcVFov();
	sector = 0;

	//std::cout << "Fov: " << Utils::radToDeg(fov) << " VFov: " << Utils::radToDeg(vfov) << "\n";
}

Camera::~Camera()
{

}

Vector2 Camera::getPosition()
{
	return position;
}

float Camera::getHeight()
{
	return height;
}

float Camera::getAngle()
{
	return angle;
}

float Camera::getFov()
{
	return fov;
}

float Camera::getFovRad()
{
	return getFov();//Utils::degToRad(fov);
}

float Camera::getVFov()
{
	return vfov;
}

uint32_t Camera::getSectorNum()
{
	return sector;
}

Vector2 Camera::convertCoords(Vector2 pos)
{
	Vector2 up{ pos.x - position.x, pos.y - position.y };
	return Vector2{up.x * sinf(Utils::degToRad(angle)) - up.y * cosf(Utils::degToRad(angle)),
					up.x * cosf(Utils::degToRad(angle)) + up.y * sinf(Utils::degToRad(angle))};
}

int Camera::screenAngleToX(float angle, int width)
{
	return (int)(width / 2.f) * (1.f - tanf(((angle) + (Utils::degToRad(fov) / 2) / Utils::degToRad(fov)) * (PI / 2) - (PI / 4)));
}

//Sets the camera position to the passed x y values
void Camera::setPosition(float x, float y)
{
	lastPosition = position;
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

void Camera::setSectorNum(uint32_t sector)
{
	this->sector = sector;
}

//Should not be used ingame, only for testing
void Camera::move(float x, float y, float h, float dt)
{
	lastPosition = position;
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

	//rect.x = (640 / 2) - 1 - 5;
	//rect.y = (360 / 2) - 1 - 5;

	rect.h = 10.f;
	rect.w = 10.f;

	SDL_SetRenderDrawColor(renderer, 0xff, 0xb2, 0xb2, 0xff);

	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0xb2, 0xff, 0xb2, 0xff);

	SDL_RenderLine(renderer, rect.x + 5, rect.y + 5,
		rect.x + 5 + 10 * cosf(Utils::degToRad(angle)), rect.y + 5 + 10 * sinf(Utils::degToRad(angle)));

	SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
	SDL_RenderLine(renderer, rect.x + 5, rect.y + 5, -2000000, rect.y + 5);

	//Camera fov visualization
	//SDL_RenderLine(renderer, position.x, position.y, position.x + 50 * cosf((angle + Utils::degToRad(45))), 
	//	position.y + 50 * sinf((Utils::degToRad(angle) + fov / 2)));
	//SDL_RenderLine(renderer, position.x, position.y, position.x + 50 * cosf((angle - Utils::degToRad(45))),
	//	position.y + 50 * sinf((Utils::degToRad(angle) - fov / 2)));
}

void Camera::draw2d(SDL_Surface* surface, uint32_t color)
{
	float radAngle = Utils::degToRad(angle + 90.f);

	Vector2 points[6];
	points[0].x = position.x;
	points[0].y = position.y - 5.f;

	points[1].x = position.x - 3.f;
	points[1].y = position.y - 0.5f;

	points[2].x = position.x + 3.f;
	points[2].y = position.y - 0.5f;

	points[3].x = position.x;
	points[3].y = position.y + 5.f;

	points[4].x = position.x - 2.f;
	points[4].y = position.y + 7.f;

	points[5].x = position.x + 2.f;
	points[5].y = position.y + 7.f;

	for (char i = 0; i < 6; ++i) 
	{
		points[i] = Utils::rotateVecAroundPoint(points[i], position, radAngle);
	}

	Utils::drawLine(surface, points[0].x, points[0].y, points[1].x, points[1].y, color);
	Utils::drawLine(surface, points[0].x, points[0].y, points[2].x, points[2].y, color);
	Utils::drawLine(surface, points[0].x, points[0].y, points[3].x, points[3].y, color);
	Utils::drawLine(surface, points[3].x, points[3].y, points[4].x, points[4].y, color);
	Utils::drawLine(surface, points[3].x, points[3].y, points[5].x, points[5].y, color);
}
