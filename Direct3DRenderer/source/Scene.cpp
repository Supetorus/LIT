#include "Scene.h"
#include "renderer/Renderer.h"
#include "resources/Skybox.h"
#include <memory>

namespace wl
{

	void Scene::Draw(const Renderer& renderer) const
	{
		for (auto model : m_models)
		{
			model->Draw(renderer);
		}
		m_skybox->Draw(renderer);
	}

	void Scene::AddModel(std::shared_ptr<Model> model)
	{
		m_models.push_back(model);
	}

	void Scene::SetSkybox(std::shared_ptr<Skybox> skybox)
	{
		m_skybox = skybox;
	}

	//void Scene::SetCamera(std::shared_ptr<Camera> camera)
	//{
	//	m_camera = camera;
	//}

}