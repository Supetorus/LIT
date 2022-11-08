#include "Model.h"
#include "renderer/Renderer.h"
#include "ImageBuffer.h"
#include "Texture.h"
#include "Sampler.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

namespace wl
{

	dx::XMFLOAT2 GetUVCoords(aiMesh *mesh, uint32_t index)
	{
		if (mesh->mTextureCoords[0] == nullptr)
			return { 0.0f, 0.0f };
		const auto coords = mesh->mTextureCoords[0][index];
		return { coords.x, coords.y };
	}

	Model::Model(const std::string &meshPath, const std::string &texturePath, std::shared_ptr<Shader> shader):
		m_shader(shader)
	{
		loadMeshes(meshPath);
		ImageBuffer image(texturePath);
		m_texture = std::make_shared<Texture>(image);
	}

	void Model::Bind()
	{
	}

	void Model::Draw(const Renderer &renderer) const
	{
		m_shader->Bind();
		m_texture->Bind(0);
		m_sampler.Bind(0);
		renderer.SetObjectMatrix(transform);
		for (Mesh mesh : m_meshes)
		{
			mesh.Bind();
			renderer.Draw(mesh.GetIndexCount());
		}
	}

	//const Mesh Model::GetMesh() const
	//{
	//	return m_meshes[0];
	//}

	const std::shared_ptr<Shader> Model::GetShader() const
	{
		return m_shader;
	}

	void Model::loadMeshes(std::string meshPath)
	{
		Assimp::Importer importer;
		auto scene = importer.ReadFile(meshPath,
			aiProcess_Triangulate
			| aiProcess_JoinIdenticalVertices
			| aiProcess_GenNormals
			| aiProcess_FlipWindingOrder //assimp uses counter clockwise winding order by default.
			| aiProcess_MakeLeftHanded // assimp uses right handed coordinates by default.
			| aiProcess_FlipUVs // assimp default is bottom left origin.
		);

		ASSERT(
			scene != nullptr,
			"Object failed to import.",
			importer.GetErrorString()
		);

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			auto assimpMesh = scene->mMeshes[i];

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

			std::vector<uint16_t> indices;
			for (unsigned int i = 0; i < assimpMesh->mNumFaces; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					indices.push_back(assimpMesh->mFaces[i].mIndices[j]);
				}
			}

			Mesh mesh;
			mesh.name = assimpMesh->mName.C_Str();
			mesh.SetVertices(vertices.data(), sizeof(Mesh::Vertex), static_cast<uint32_t>(vertices.size()));
			mesh.SetIndices(indices.data(), static_cast<uint32_t>(indices.size()));

			m_meshes.push_back(mesh);
		}
	}

}