#include "Camera.h"
#include "Input.h"

namespace wl
{

	//Camera::Camera(const Object &parent, float width, float height):
	//	perspectiveWidth(width),
	//	perspectiveHeight(height),
	//	Component(parent)
	//{}

	void Camera::Update(float dt)
	{
		float speed = 1.0f;
		const char space = 0x20;
		const char shift = 0x10;
		if (Input::Instance.GetKeyDown('A'))	transform.posX -= speed * dt;
		if (Input::Instance.GetKeyDown('D'))	transform.posX += speed * dt;
		if (Input::Instance.GetKeyDown('W'))	transform.posZ += speed * dt;
		if (Input::Instance.GetKeyDown('S'))	transform.posZ -= speed * dt;
		if (Input::Instance.GetKeyDown(space))	transform.posY += speed * dt;
		if (Input::Instance.GetKeyDown(shift))	transform.posY -= speed * dt;

		float rSpeed = 1.0f;
		const char left = 0x25;
		const char right = 0x27;
		const char up = 0x26;
		const char down = 0x28;
		if (Input::Instance.GetKeyDown(left))	transform.angleY -= speed * dt;
		if (Input::Instance.GetKeyDown(right))	transform.angleY += speed * dt;
		if (Input::Instance.GetKeyDown(up))		transform.angleX -= speed * dt;
		if (Input::Instance.GetKeyDown(down))	transform.angleX += speed * dt;


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
