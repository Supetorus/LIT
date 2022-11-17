#pragma once
#include <memory>

namespace wl
{
	class Camera;
	class Scene;
	class Model;

	class Controller
	{
	public:
		Controller(Camera &camera, std::shared_ptr<Scene> &scene);
		void Update(float deltaTime);
	private:
		Camera &m_camera;
		std::shared_ptr<Scene> &m_scene;
		bool m_isCameraMode{ true };
		int m_currentModel{};
	};

}
