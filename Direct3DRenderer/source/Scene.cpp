#include "Scene.h"
#include "renderer/Renderer.h"

namespace wl
{

	void Scene::Draw(const Renderer& renderer) const
	{
		for (auto model : m_models)
		{
			model->Draw(renderer);
		}
	}

	void Scene::AddModel(std::shared_ptr<Model> model)
	{
		m_models.push_back(model);
	}

}