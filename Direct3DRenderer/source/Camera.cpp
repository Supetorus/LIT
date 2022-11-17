#include "Camera.h"
#include "Input.h"
#include "core/util.h"

namespace wl
{

	//Camera::Camera(const Object &parent, float width, float height):
	//	perspectiveWidth(width),
	//	perspectiveHeight(height),
	//	Component(parent)
	//{}

	void Camera::Update(float dt)
	{
		ManipulateTransform(transform, 1, 0, 1, dt);
	}

	void Camera::SetNearPlane(float distance)
	{
		nearPlane = distance;
	}

	void Camera::SetFarPlane(float distance)
	{
		farPlane = distance;
	}

}
