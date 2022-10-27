#include "App.h"
#include "core/Log.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/Shader.h"
#include "Mesh.h"
#include "Model.h"

namespace wl
{

	void App::Init()
	{
		timer.Reset();
		renderer = std::make_unique<Renderer>(window);
	}

	Model ImportModel()
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

		//Vertex input layout
		wrl::ComPtr<ID3D11InputLayout> pInputLayout;
		D3D11_INPUT_ELEMENT_DESC elemDescs[]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		Shader shader(L"../Assets/Shaders/PixelShader.cso", L"../Assets/Shaders/VertexShader.cso");
		shader.SetLayout(elemDescs, std::size(elemDescs));

		return Model(cube, shader, colorBuffer);
	}

	void App::Run()
	{
		while (!window.IsQuit())
		{
			window.DoMessagePump();
			timer.Tick();
			
			renderer->BeginFrame();

			// "import" model(s)
			Model cube = ImportModel();
			
			// Draw all objects
			cube.Draw(*renderer);

			renderer->EndFrame();
		}

		window.Close();
	}

}