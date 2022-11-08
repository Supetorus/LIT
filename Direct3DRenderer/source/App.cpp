#include "App.h"
#include "core/Log.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/Shader.h"
#include "Object.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "ImageBuffer.h"
#include "Camera.h"
#include "Sampler.h"
#include "Input.h"
#include <filesystem>

constexpr float pi = 3.14159265359;
constexpr float halfPi = pi / 2;
constexpr float radToDeg = halfPi / 3.14159f;
constexpr float degToRad = pi / 180;

namespace wl
{

	//Model *MakeCube(std::shared_ptr<Shader> shader)
	//{
	//	const Mesh::Vertex vertices[]
	//	{
	//		{dx::XMFLOAT3(-1.0f, -1.0f, -1.0f), },
	//		{dx::XMFLOAT3(1.0f, -1.0f, -1.0f), },
	//		{dx::XMFLOAT3(-1.0f,  1.0f, -1.0f), },
	//		{dx::XMFLOAT3(1.0f,  1.0f, -1.0f), },
	//		{dx::XMFLOAT3(-1.0f, -1.0f,  1.0f), },
	//		{dx::XMFLOAT3(1.0f, -1.05,  1.0f), },
	//		{dx::XMFLOAT3(-1.0f,  1.0f,  1.0f), },
	//		{dx::XMFLOAT3(1.0f,  1.0f,  1.0f), },
	//	};
	//	uint16_t indices[]{
	//		0, 2, 1, 2, 3, 1,
	//		1, 3, 5, 3, 7, 5,
	//		2, 6, 3, 3, 6, 7,
	//		4, 5, 7, 4, 7, 6,
	//		0, 4, 2, 2, 4, 6,
	//		0, 1, 4, 1, 5, 4,
	//	};
	//	Renderer::ColorList faceColors
	//	{
	//		{
	//			{1.0f, 0.0f, 1.0f},
	//			{1.0f, 0.0f, 0.0f},
	//			{0.0f, 1.0f, 0.0f},
	//			{0.0f, 0.0f, 1.0f},
	//			{1.0f, 1.0f, 0.0f},
	//			{0.0f, 1.0f, 1.0f},
	//		}
	//	};
	//	Mesh cube;
	//	cube.SetVertices(vertices, sizeof(Mesh::Vertex), static_cast<uint32_t>(std::size(vertices)));
	//	cube.SetIndices(indices, static_cast<uint32_t>(std::size(indices)));
	//	// "Import" "Textures"
	//	ConstantBuffer colorBuffer(sizeof(Renderer::ColorList), ShaderStage::Pixel);
	//	colorBuffer.SetData(&faceColors);
	//	return new Model(cube, shader, colorBuffer);
	//}

	void App::Init()
	{
		m_gTimer.Reset();
		m_renderer = std::make_unique<Renderer>(m_window);
		std::filesystem::current_path("assets/");
	}

	void App::Run()
	{
		std::shared_ptr<Shader> defaultShader = std::make_shared<Shader>();
		Model model("models/skull.obj", "skull.jpg", defaultShader);
		model.transform.scale = { 0.1f, 0.1f, 0.1f };

		std::shared_ptr<Camera> camera = std::make_shared<Camera>();
		camera->transform.position.z = -20;
		m_renderer->SetCamera(camera);

		//m_renderer->SetModeWireframe();

		// Main loop
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			Input::Instance.UpdateKeyStates();
			m_gTimer.Tick();

			camera->Update(m_gTimer.GetDeltaTime());
			model.transform.rotation.y += m_gTimer.GetDeltaTime();

			m_renderer->BeginFrame();

			m_renderer->SetViewProjectionMatrix();
			model.Draw(*m_renderer);

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}