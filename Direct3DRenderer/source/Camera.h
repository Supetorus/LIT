#pragma once
#include "Transform.h"
#include "Component.h"
#include "Object.h"

namespace wl
{

	class Camera: public Component
	{
	public:
		Camera() = delete;
		Camera(const Object &parent, float width, float height);
		void SetNearPlane(float distance);
		void SetFarPlane (float distance);
	private:
		float perspectiveWidth = 1;
		float perspectiveHeight = 1.333333f;
		float nearPlane = 0.5f;
		float farPlane = 10.0f;
	};

}
