#include "App.h"
#include "core/Log.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/Shader.h"
#include "Object.h"
#include "resources/Mesh.h"
#include "resources/Model.h"
#include "resources/Texture.h"
#include "resources/ImageBuffer.h"
#include "Camera.h"
#include "resources/Sampler.h"
#include "Input.h"
#include "resources/CubeMap.h"
#include <filesystem>
#include <resources/Skybox.h>

constexpr float pi = 3.14159265359;
constexpr float halfPi = pi / 2;
constexpr float radToDeg = halfPi / 3.14159f;
constexpr float degToRad = pi / 180;

namespace wl
{

	App::~App()
	{
		//for (Model *model : m_models) delete model;
	}

	void App::Init()
	{
		m_gTimer.Reset();
		m_renderer = std::make_unique<Renderer>(m_window);
		std::filesystem::current_path("assets/");
	}

	void App::Run()
	{
#pragma region LoadModels
		std::shared_ptr<Shader> defaultShader = std::make_shared<Shader>();
		Model skull("models/skull.obj", "skull.jpg", defaultShader, "Skull");
		skull.transform =
		{
			.position = {0, -1.5, 0},
			.scale = {0.05f, 0.05f, 0.05f},
			.rotation = {90 * degToRad, 0, 0}
		};
		m_models.push_back(&skull);
		Model cube("models/cube.obj", "flower.jpg", defaultShader, "Cube");
		cube.transform.position = { -2, 0, 0 };
		m_models.push_back(&cube);
		//Model cube("models/invertedCube.obj", "cubemaps/test/posx.jpg", defaultShader, "Cube");
		//cube.transform.position = { -2, 0, 0 };
		//m_models.push_back(&cube);
		Model sphere("models/sphere.obj", "obsidian.png", defaultShader, "Sphere");
		sphere.transform.position = { 2, 0, 0 };
		m_models.push_back(&sphere);
		Model ogre("models/ogre.obj", "ogre_diffuse.bmp", defaultShader, "Ogre");
		ogre.transform.position = { 0, 1, 0 };
		m_models.push_back(&ogre);

		std::shared_ptr<Camera> camera = std::make_shared<Camera>();
		camera->transform.position.z = -5;
		m_renderer->SetCamera(camera);
		LOG("Scene Loaded");
#pragma endregion
		Skybox skybox("Storforsen3");

		//m_renderer->SetModeWireframe();

		// Main loop
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			Input::Instance.UpdateKeyStates();
			m_gTimer.Tick();

			camera->Update(m_gTimer.GetDeltaTime());

			skull.transform.rotation.y += m_gTimer.GetDeltaTime();
			ogre.transform.rotation.y -= m_gTimer.GetDeltaTime();

			m_renderer->BeginFrame();

			m_renderer->SetViewProjectionMatrix();
			for (Model *model : m_models)
			{
				model->Draw(*m_renderer);
			}

			skybox.Draw(*m_renderer);

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}