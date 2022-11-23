#include "Skybox.h"
#include "resources/Mesh.h"
#include "resources/CubeMap.h"
#include "utilities/MeshLoader.h"
#include "renderer/Renderer.h"
#include "Transform.h"

namespace wl
{

	static std::shared_ptr<Mesh> MakeInvertedCube()
	{
		struct Vertex
		{
			dx::XMFLOAT3 Pos;
		};
		
		Vertex *vertices = new Vertex[]
		{
			{{  1.0f,  1.0f, -1.0f }}, //1 back right top
			{{  1.0f, -1.0f, -1.0f }}, //2 back right bottom
			{{  1.0f,  1.0f,  1.0f }}, //3 front right top
			{{  1.0f, -1.0f,  1.0f }}, //4 front right bottom
			{{ -1.0f,  1.0f, -1.0f }}, //5 back left top
			{{ -1.0f, -1.0f, -1.0f }}, //6 back left bottom
			{{ -1.0f,  1.0f,  1.0f }}, //7 front left top
			{{ -1.0f, -1.0f,  1.0f }}, //8 front left bottom
		};

		uint16_t *indices = new uint16_t[]
		{
			//right face +x
			0, 1, 2,
			1, 3, 2,
			//close face -z
			0, 4, 5,
			0, 5, 1,
			//left face -x
			4, 6, 7,
			4, 7, 5,
			//far face +z
			6, 2, 3,
			6, 3, 7,
			//top face +y
			6, 4, 2,
			2, 4, 0,
			//bottom face -y
			7, 3, 5,
			3, 1, 5,
		};

		Mesh::SubMesh *subMesh = new Mesh::SubMesh;
		subMesh->name = "Inverted Cube";
		subMesh->SetVertices(vertices, sizeof(Vertex), 8);
		subMesh->SetIndices(indices, 36);
		
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->AddSubMesh(subMesh);

		return mesh;
	}

	Skybox::Skybox(const std::string &texturePath)
	{
		m_shader = std::make_shared<Shader>(L"shaders/Skybox_Pixel.cso", L"shaders/Skybox_Vertex.cso", "Skybox");
		m_cubeMesh = MakeInvertedCube();
		m_cubemap = std::make_shared<CubeMap>(texturePath);
	}

	void Skybox::Draw(const Renderer &renderer)
	{
		m_shader->Bind();
		m_cubemap->Bind(0);
		m_sampler.Bind(0);
		m_cubeMesh->Draw(renderer);
	}

	const CubeMap &Skybox::GetCubeMap() const
	{
		return *m_cubemap;
	}

}