#include "App.h"
#include "core/Log.h"
#include "renderer/Renderer.h"
#include "resources/Model.h"
#include "Camera.h"
#include "Input.h"
#include "Scene.h"
#include "utilities/SceneSerializer.h"
#include "Controller.h"
#include <memory>
#include <filesystem>

constexpr float pi = 3.14159265359;
constexpr float halfPi = pi / 2;
constexpr float radToDeg = halfPi / 3.14159f;
constexpr float degToRad = pi / 180;

namespace wl
{
	void App::Init()
	{
		std::filesystem::current_path("assets/");
		m_gTimer.Reset();
		m_renderer = std::make_unique<Renderer>(m_window);
		m_scene = std::make_shared<Scene>();
	}

	void App::Run()
	{
		//std::shared_ptr<Camera> camera = std::make_shared<Camera>();
		//camera->transform.position.z = -5;
		LOG("Scene Loaded");

		{
			SceneSerializer serializer;
			//serializer.Serialize("scenes/test.scn", *m_scene);
			m_scene = serializer.Deserialize("scenes/test1.scn");
		}
		m_renderer->SetCamera(m_scene->m_camera);

		//m_renderer->SetModeWireframe();
		Controller controller(m_scene, *m_renderer);
		// Main loop
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			Input::Instance.UpdateKeyStates();
			m_gTimer.Tick();

			//camera->Update(m_gTimer.GetDeltaTime());
			controller.Update(m_gTimer.GetDeltaTime());

			m_renderer->BeginFrame();

			m_renderer->SetViewProjectionMatrix();
			m_scene->Draw(*m_renderer);

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}