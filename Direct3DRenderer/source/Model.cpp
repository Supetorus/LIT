#include "Model.h"

#include "renderer/Renderer.h"

namespace wl
{
	Model::Model(Mesh mesh, std::shared_ptr<Shader> shader, ConstantBuffer colorbuffer):
		m_mesh(mesh),
		m_shader(shader),
		m_buffer(colorbuffer)
	{}

	void Model::Bind()
	{
		m_shader->Bind();
		m_mesh.Bind();
		m_buffer.Bind();
	}

	const Mesh Model::GetMesh() const
	{
		return m_mesh;
	}

	const std::shared_ptr<Shader> Model::GetShader() const
	{
		return m_shader;
	}

	const ConstantBuffer Model::GetColorBuffer() const
	{
		return m_buffer;
	}

}