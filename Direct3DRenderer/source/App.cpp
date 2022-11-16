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
#include "Scene.h"
#include "renderer/Renderer.h"
#include "resources/Skybox.h"
#include "SceneSerializer.h"
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
		std::shared_ptr<Shader> defaultShader = std::make_shared<Shader>();
#pragma region LoadModels
		/*std::shared_ptr<Model> skull = std::make_shared<Model>("models/skull.obj", "skull.jpg", defaultShader, "Skull");
		skull->transform =
		{
			.position = {0, -1.5, 0},
			.scale = {0.05f, 0.05f, 0.05f},
			.rotation = {90 * degToRad, 0, 0}
		};
		m_scene->AddModel(skull);

		std::shared_ptr<Model> sphere = std::make_shared<Model>("models/sphere.obj", "obsidian.png", defaultShader, "Sphere");
		sphere->transform.position = { 2, 0, 0 };
		m_scene->AddModel(sphere);

		std::shared_ptr<Model> ogre = std::make_shared<Model>("models/ogre.obj", "ogre_diffuse.bmp", defaultShader, "Ogre");
		ogre->transform.position = { 0, 1, 0 };
		m_scene->AddModel(ogre);

		std::shared_ptr <Model> cube = std::make_shared<Model>("models/cube.obj", "flower.jpg", defaultShader, "Cube");
		cube->transform.position = { -2, 0, 0 };
		m_scene->AddModel(cube);
		*/
		std::shared_ptr<Camera> camera = std::make_shared<Camera>();
		camera->transform.position.z = -5;
		m_renderer->SetCamera(camera);
		LOG("Scene Loaded");

		SceneSerializer serializer;
		//serializer.Serialize("scenes/test.scn", *m_scene);
		m_scene = serializer.Deserialize("scenes/test.scn");
#pragma endregion

		//m_renderer->SetModeWireframe();

		// Main loop
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			Input::Instance.UpdateKeyStates();
			m_gTimer.Tick();

			camera->Update(m_gTimer.GetDeltaTime());

			//skull->transform.rotation.y += m_gTimer.GetDeltaTime();
			//ogre->transform.rotation.y -= m_gTimer.GetDeltaTime();

			m_renderer->BeginFrame();

			m_renderer->SetViewProjectionMatrix();
			m_scene->Draw(*m_renderer);

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}