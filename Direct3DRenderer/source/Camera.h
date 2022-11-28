#pragma once
#include "Transform.h"
//#include "Component.h"
//#include "Object.h"

namespace wl
{

	class Transform;

	class Camera//: public Component
	{
	public:
		Camera() = default;
		Transform transform;
		float fov = 45.0f; // in degrees
		float nearPlane = 0.5f;
		float farPlane = 50.0f;
		float clearColor[4] { 0.5f, 0.5f, 0.5f, 1.0f };
	};

}
