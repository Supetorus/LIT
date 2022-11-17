#pragma once
#include "resources/Model.h"
#include <vector>
#include <memory>

namespace wl
{
	class Renderer;
	class Skybox;
	class Camera;

	class Scene
	{
		friend class SceneSerializer;
		friend class Controller;

	public:
		void Draw(const Renderer &renderer) const;
		void AddModel(std::shared_ptr<Model> model);
		void SetSkybox(std::shared_ptr<Skybox> skybox);
		//void SetCamera(std::shared_ptr<Camera> camera);
		std::shared_ptr<Camera> m_camera;
	private:
		std::string m_filepath{};
		std::vector<std::shared_ptr<Model>> m_models;
		std::shared_ptr<Skybox> m_skybox;
	};

}
