#include "Object.h"
#include "renderer/Renderer.h"

namespace wl
{
	Object::Object(Transform transform, Model *model) :
		m_transform(transform),
		m_model(model)
	{}

	void wl::Object::Draw(const Renderer &renderer) const
	{
		if (!m_model) return;
		m_model->Bind();
		renderer.Draw(*m_model, m_transform);
	}

}