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
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <filesystem>

constexpr float pi = 3.14159265359;
constexpr float halfPi = pi / 2;
constexpr float radToDeg = halfPi / 3.14159f;
constexpr float degToRad = pi / 180;

namespace wl
{

	Model *MakeCube(std::shared_ptr<Shader> shader)
	{
		const Mesh::Vertex vertices[]
		{
			{dx::XMFLOAT3(-1.0f, -1.0f, -1.0f), },
			{dx::XMFLOAT3(1.0f, -1.0f, -1.0f), },
			{dx::XMFLOAT3(-1.0f,  1.0f, -1.0f), },
			{dx::XMFLOAT3(1.0f,  1.0f, -1.0f), },
			{dx::XMFLOAT3(-1.0f, -1.0f,  1.0f), },
			{dx::XMFLOAT3(1.0f, -1.05,  1.0f), },
			{dx::XMFLOAT3(-1.0f,  1.0f,  1.0f), },
			{dx::XMFLOAT3(1.0f,  1.0f,  1.0f), },
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
		cube.SetVertices(vertices, sizeof(Mesh::Vertex), static_cast<uint32_t>(std::size(vertices)));
		cube.SetIndices(indices, static_cast<uint32_t>(std::size(indices)));
		// "Import" "Textures"
		ConstantBuffer colorBuffer(sizeof(Renderer::ColorList), ShaderStage::Pixel);
		colorBuffer.SetData(&faceColors);

		return new Model(cube, shader, colorBuffer);
	}

	void App::Init()
	{
		m_gTimer.Reset();
		m_renderer = std::make_unique<Renderer>(m_window);
		std::filesystem::current_path("assets/");

		// Create camera
		//Object cameraObject;
		//cameraObject.components.push_back(new Camera(cameraObject, 1, 1.3333333f));
		//m_objects.push_back(cameraObject);

		// "import" model(s)
		//Model *cube1 = MakeCube(shader);
		//Object o1({ -2, 0, 6, 45.f * degToRad, 45.f * degToRad, 45.f * degToRad }, cube1);
		//Object o2({  2, 0, 6, 45.f * degToRad, 0, 45.f * degToRad }, cube1);
		//m_objects.push_back(o1);
		//m_objects.push_back(o2);

	}

	dx::XMFLOAT2 GetUVCoords(aiMesh *mesh, uint32_t index)
	{
		if (mesh->mTextureCoords[0] == nullptr)
			return { 0.0f, 0.0f };
		const auto coords = mesh->mTextureCoords[0][index];
		return { coords.x, coords.y };
	}

	void App::Run()
	{
		//const Mesh::Vertex faceVertices[]
		//{
		//	{dx::XMFLOAT3(-1.0f, -1.0f, 0), dx::XMFLOAT2(0, 1) }, // bottom left
		//	{dx::XMFLOAT3( 1.0f, -1.0f, 0), dx::XMFLOAT2(1, 1) }, // bottom right
		//	{dx::XMFLOAT3(-1.0f,  1.0f,0),  dx::XMFLOAT2(0, 0) }, // top left
		//	{dx::XMFLOAT3( 1.0f,  1.0f, 0), dx::XMFLOAT2(1, 0) }, // top right
		//};

		//uint16_t faceIndices[]{
		//	0,2,3,
		//	0,3,1,
		//};
		
		// Initialize shader to be used by models.

		Shader shader;
		//D3D11_INPUT_ELEMENT_DESC elemDescs[]
		//{
		//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//	//{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//};
		//shader.SetLayout(elemDescs, 2);

#pragma region LoadMesh

		// Make mesh
		Mesh mesh;
		Assimp::Importer importer;
		auto scene = importer.ReadFile("models/quad.obj",
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_GenNormals |
			aiProcess_FlipWindingOrder | //assimp uses counter clockwise winding order by default.
			aiProcess_MakeLeftHanded |// assimp uses right handed coordinates by default.
			aiProcess_FlipUVs // assimp default is bottom left origin.
		);

		ASSERT(
			scene != nullptr,
			"Object failed to import.",
			importer.GetErrorString()
		);

		auto assimpMesh = scene->mMeshes[0];

		std::vector<Mesh::Vertex> vertices;
		for (unsigned int i = 0; i < assimpMesh->mNumVertices; i++)
		{
			vertices.push_back(
				Mesh::Vertex
				{
					{
						assimpMesh->mVertices[i].x,
						assimpMesh->mVertices[i].y,
						assimpMesh->mVertices[i].z,
					},
					GetUVCoords(assimpMesh, i)
				}
			);
		}
		mesh.SetVertices(vertices.data(), sizeof(Mesh::Vertex), static_cast<uint32_t>(vertices.size()));

		std::vector<uint16_t> indices;
		//int indexCount = assimpMesh->mNumFaces * 3;
		for (unsigned int i = 0; i < assimpMesh->mNumFaces; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				indices.push_back(assimpMesh->mFaces[i].mIndices[j]);
			}
		}

		mesh.SetIndices(indices.data(), static_cast<uint32_t>(indices.size()));
#pragma endregion

		// Make Texture
		ImageBuffer image("nature.png");
		Texture texture(image);
		Sampler sampler;

		Transform transform{0, 0 , 2}; // zeroes.

		//m_renderer->SetModeWireframe();

		// Main loop
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			m_gTimer.Tick();

			m_renderer->BeginFrame();

			transform.angleY += m_gTimer.DeltaTime();

			shader.Bind();
			mesh.Bind();
			texture.Bind(0);
			sampler.Bind(0);

			m_renderer->SetupPerspective(transform);
			m_renderer->Draw(mesh.GetIndexCount());

			//for (int i = 0; i < m_objects.size(); i++)
			//{
			//	//m_objects[i].m_transform.angleZ += m_gTimer.DeltaTime();
			//	m_objects[i].m_transform.angleY += m_gTimer.DeltaTime();
			//	m_objects[i].Draw(*m_renderer);
			//}

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}