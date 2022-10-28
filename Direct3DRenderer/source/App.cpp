#include "App.h"
#include "core/Log.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/Shader.h"
#include "Object.h"
#include "Mesh.h"
#include "Model.h"
#include <Camera.h>

constexpr float pi = 3.14159265359;
constexpr float halfPi = pi / 2;
constexpr float radToDeg = halfPi / 3.14159f;
constexpr float degToRad = pi / 180;

namespace wl
{

	Model* MakeCube(Shader *shader)
	{
		const Renderer::Vertex vertices[]
		{
			{-1.0f, -1.0f, -1.0f},
			{ 1.0f, -1.0f, -1.0f},
			{-1.0f,  1.0f, -1.0f},
			{ 1.0f,  1.0f, -1.0f},
			{-1.0f, -1.0f,  1.0f},
			{ 1.0f, -1.05,  1.0f},
			{-1.0f,  1.0f,  1.0f},
			{ 1.0f,  1.0f,  1.0f},
		};
		uint16_t indices[]{
			0, 2, 1, 2, 3, 1,
			1, 3, 5, 3, 7, 5,
			2, 6, 3, 3, 6, 7,
			4, 5, 7, 4, 7, 6,
			0, 4, 2, 2, 4, 6,
			0, 1, 4, 1, 5, 4,
		};
		Renderer::ColorList faceColors
		{
			{
				{1.0f, 0.0f, 1.0f},
				{1.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 1.0f},
				{1.0f, 1.0f, 0.0f},
				{0.0f, 1.0f, 1.0f},
			}
		};

		Mesh cube;
		cube.SetVertices(vertices, sizeof(Renderer::Vertex), std::size(vertices));
		cube.SetIndices(indices, std::size(indices));
		// "Import" "Textures"
		ConstantBuffer colorBuffer(sizeof(Renderer::ColorList), ShaderStage::Pixel);
		colorBuffer.SetData(&faceColors);

		return new Model(cube, shader, colorBuffer);
	}

	void App::Init()
	{
		m_gTimer.Reset();
		m_renderer.emplace(Renderer(m_window));

		// Initialize shader to be used by models.
		Shader* shader = new Shader();
		shader->SetLayout();

		// Create camera
		Object cameraObject;
		cameraObject.components.push_back(new Camera(cameraObject, 1, 1.3333333f));
		m_objects.push_back(cameraObject);

		// "import" model(s)
		Model *cube1 = MakeCube(shader);
		Object o1({ -2, 0, 6, 45.f * degToRad, 45.f * degToRad, 45.f * degToRad }, cube1);
		Object o2({  2, 0, 6, 45.f * degToRad, 0, 45.f * degToRad }, cube1);
		m_objects.push_back(o1);
		m_objects.push_back(o2);
	}

	void App::Run()
	{
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			m_gTimer.Tick();

			m_renderer->BeginFrame();
			for (int i = 0; i < m_objects.size(); i++)
			{
				//m_objects[i].m_transform.angleZ += m_gTimer.DeltaTime();
				m_objects[i].m_transform.angleY += m_gTimer.DeltaTime();
				m_objects[i].Draw(*m_renderer);
			}

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}