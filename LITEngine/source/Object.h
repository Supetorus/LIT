#pragma once

#include "Transform.h"
#include "resources/Model.h"
#include <vector>

namespace lit
{
	class Component;
	class Renderer;

	class Object
	{
	public:
		Object() = default;
		Object(Transform transform, Model *model = nullptr);
		void Draw(const Renderer &renderer) const;
		Transform m_transform;
		std::vector<Component*> components{};
		Model *m_model{};
	};
}