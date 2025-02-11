#include "Camera.h"

Camera::Camera()
{
	position.x = 0.f;
	position.y = 0.f;
	angle = 0.f;
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

}

//Sets the camera position to the passes x y values and sets height to the passed value
void Camera::setPosition(float x, float y, float height)
{
	setPosition(x, y);
	//Set Height
}

//Sets the camera's rotation to the passed value
void Camera::setAngle(float angle)
{
	this->angle = angle;
}
