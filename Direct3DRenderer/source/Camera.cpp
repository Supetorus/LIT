#include "Camera.h"

namespace wl
{

	Camera::Camera(const Object &parent, float width, float height):
		perspectiveWidth(width),
		perspectiveHeight(height),
		Component(parent)
	{}

	void Camera::SetNearPlane(float distance)
	{
		nearPlane = distance;
	}

	void Camera::SetFarPlane(float distance)
	{
		farPlane = distance;
	}

}
