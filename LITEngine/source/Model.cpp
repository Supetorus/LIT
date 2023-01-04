#include "Model.h"
#include "Renderer.h"
#include "ImageBuffer.h"
#include "Texture.h"
#include "Sampler.h"
#include "MeshLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <memory>

namespace lit
{
	Model::Model(const std::string &meshPath, const std::string &texturePath, std::shared_ptr<Shader> shader, std::string name) :
		m_shader(shader),
		name(name),
		m_meshPath(meshPath),
		m_texturePath(texturePath)
	{
		m_mesh = MeshLoader::LoadMesh(meshPath);
		ImageBuffer image(texturePath);
		m_texture = std::make_shared<Texture>(image);
	}

	void Model::Draw(const Renderer &renderer) const
	{
		m_shader->Bind();
		m_texture->Bind(0);
		m_sampler.Bind(0);
		renderer.SetModelMatrix(transform);
		m_mesh->Draw(renderer);
	}

	const std::shared_ptr<Shader> Model::GetShader() const
	{
		return m_shader;
	}

	std::shared_ptr<Model> Model::Clone() const
	{
		std::shared_ptr<Model> model = std::make_shared<Model>(m_meshPath, m_texturePath, m_shader, name);
		model->transform = transform;
		return model;
	}

}