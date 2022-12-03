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
		{
			SceneSerializer serializer;
			m_scene = serializer.Deserialize("scenes/test2.scn");
		}
		m_renderer->SetCamera(m_scene->m_camera);

		Controller controller(m_scene, *m_renderer);

		//PointLight pointLight;
		//pointLight.Bind(*m_scene->m_camera);

		//struct objectLightInfo
		//{
		//	alignas(16) float specularIntensity = 0.6f;
		//	float specularPower = 30.0f;
		//} data{};

		//ConstantBuffer objLight(sizeof(objectLightInfo), ShaderStage::Pixel);
		//objLight.SetData(&data);
		//objLight.Bind(1);

#pragma region lightStuff
		struct LightData
		{
			dx::XMFLOAT4 ambient{ 0.2f, 0.2f, 0.2f, 0 };
			dx::XMFLOAT4 diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
			dx::XMFLOAT4 specular{ 1.0f, 1.0f, 1.0f, 1.0f };
			alignas(16) dx::XMFLOAT3 position{ 0, 0, 0 };
			alignas(16) dx::XMFLOAT3 attenuation{ 1.0f, 0.045f, 0.0075f };
			float range{ 50 };
		} light;

		struct MaterialData
		{
			dx::XMFLOAT4 ambient{ 1.0f, 1.0f, 1.0f, 1.0f };
			dx::XMFLOAT4 diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
			dx::XMFLOAT4 specular{ 1.0f, 1.0f, 1.0f, 1.0f };
			dx::XMFLOAT4 reflect{};
		} material;

		struct CameraPosition
		{
			alignas(16) dx::XMFLOAT3 position;
		} camera;

		ConstantBuffer l(sizeof(LightData), ShaderStage::Pixel);
		ConstantBuffer m(sizeof(LightData), ShaderStage::Pixel);
		ConstantBuffer c(sizeof(LightData), ShaderStage::Pixel);

		l.SetData(&light);
		m.SetData(&material);
		
		l.Bind(0);
		m.Bind(1);
#pragma endregion

		// Main loop
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			Input::Instance.UpdateKeyStates();
			m_gTimer.Tick();

			//camera->Update(m_gTimer.GetDeltaTime());
			controller.Update(m_gTimer.GetDeltaTime());

#pragma region temp
		const Transform::f3 &t = m_scene->m_camera->transform.position;
			camera.position = dx::XMFLOAT3{ t.x, t.y, t.z };
			c.SetData(&camera);
			c.Bind(2);
#pragma endregion

			m_renderer->BeginFrame();

			m_scene->Draw(*m_renderer);

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}