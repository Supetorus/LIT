#pragma once
#include <memory>

namespace lit
{
	class Camera;
	class Scene;
	class Model;
	class Renderer;

	class Controller
	{
	public:
		Controller(std::shared_ptr<Scene> &scene, Renderer &renderer);
		void Update(float deltaTime);
	private:
		Renderer &m_renderer;
		std::shared_ptr<Scene> &m_scene;
		bool m_isCameraMode{ true };
		int m_currentModel{};
		bool m_isWireframe{ false };
		float m_cameraSpeed{ 1 };
		float m_controllerSpeed{ 1 };
	};

}
