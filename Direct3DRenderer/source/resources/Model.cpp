#include "Model.h"
#include "renderer/Renderer.h"
#include "ImageBuffer.h"
#include "Texture.h"
#include "Sampler.h"
#include "utilities/MeshLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

	dx::XMFLOAT2 GetUVCoords(aiMesh *mesh, uint32_t index)
	{
		if (mesh->mTextureCoords[0] == nullptr)
			return { 0.0f, 0.0f };
		const auto coords = mesh->mTextureCoords[0][index];
		return { coords.x, coords.y };
	}

namespace wl
{
	Model::Model(const std::string &meshPath, const std::string &texturePath, std::shared_ptr<Shader> shader, std::string name):
		m_shader(shader),
		name(name)
	{
		//loadMeshes(meshPath);
		m_meshes = MeshLoader::LoadMeshes(meshPath);
		ImageBuffer image(texturePath);
		m_texture = std::make_shared<Texture>(image);
	}

	Model::~Model()
	{
		for (Mesh *mesh : *m_meshes) delete mesh;
		delete m_meshes;
	}

	void Model::Draw(const Renderer &renderer) const
	{
		m_shader->Bind();
		m_texture->Bind(0);
		m_sampler.Bind(0);
		renderer.SetObjectMatrix(transform);
		for (Mesh *mesh : *m_meshes)
		{
			mesh->Bind();
			renderer.Draw(mesh->GetIndexCount());
		}
	}

	const std::shared_ptr<Shader> Model::GetShader() const
	{
		return m_shader;
	}

}