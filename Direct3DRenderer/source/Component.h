#pragma once

#include "Object.h"
#include "Transform.h"

namespace wl
{

	class Component
	{
	public:
		Component() = delete;
		Component(const Object &parent);
		const Object &parent;
		const Transform &transform;
	};

}