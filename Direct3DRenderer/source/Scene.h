#pragma once
#include "resources/Model.h"
#include <vector>
#include <memory>

namespace wl
{
	class Renderer;
	class Skybox;

	class Scene
	{
		friend class SceneSerializer;
	public:
		Scene();
		void Draw(const Renderer &renderer) const;
		void AddModel(std::shared_ptr<Model> model);
		void SetSkybox(std::shared_ptr<Skybox> skybox);
	private:
		std::vector<std::shared_ptr<Model>> m_models;
		std::shared_ptr<Skybox> m_skybox;
	};

}
