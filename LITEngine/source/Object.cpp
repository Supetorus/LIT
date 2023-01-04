#include "Object.h"
#include "Renderer.h"

namespace lit
{

	Object::Object(Transform transform, Model *model) :
		m_transform(transform),
		m_model(model)
	{}

	void lit::Object::Draw(const Renderer &renderer) const
	{
		renderer;
		//if (!m_model) return;
		//m_model->Bind();
		//renderer.Draw(*m_model, m_transform);
	}

}