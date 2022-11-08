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
		float perspectiveWidth = 1;
		float perspectiveHeight = 1.333333f;
		float nearPlane = 0.5f;
		float farPlane = 50.0f;
	};

}
