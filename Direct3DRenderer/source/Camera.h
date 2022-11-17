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
		void Update(float dt);
		//Camera(const Object &parent, float width, float height);
		void SetNearPlane(float distance);
		void SetFarPlane (float distance);
		Transform transform;
		float fov = 45.0f; // in degrees
		float nearPlane = 0.5f;
		float farPlane = 50.0f;
	};

}
