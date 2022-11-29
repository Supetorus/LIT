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
#include <PointLight.h>

namespace wl
{
	App::App()
	{
		std::filesystem::current_path("assets/");
		m_gTimer.Reset();
		m_renderer = std::make_unique<Renderer>(m_window);
		m_scene = std::make_shared<Scene>();
	}

	void App::Run()
	{
		PointLight pointLight;
		pointLight.Bind();

		{
			SceneSerializer serializer;
			m_scene = serializer.Deserialize("scenes/demo.scn");
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

			m_scene->Draw(*m_renderer);

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}