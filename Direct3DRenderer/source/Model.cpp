#include "Model.h"

#include "renderer/Renderer.h"
namespace wl
{
	Model::Model(Mesh mesh, Shader shader, ConstantBuffer colorbuffer):
		m_mesh(mesh),
		m_shader(shader),
		m_cBuffer(colorbuffer)
	{
		//m_mesh = mesh;
		//m_shader = shader;
		//m_cBuffer = colorbuffer;
	}

	void Model::Draw(Renderer renderer)
	{
		m_shader->Bind();
		m_mesh->Bind();
		m_cBuffer->Bind(0);

		renderer.Draw(m_mesh->GetIndexCount());
	}
}