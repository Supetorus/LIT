#include "Mesh.h"
#include "Renderer.h"

namespace lit
{

	void Mesh::SubMesh::SetVertices(const void *data, uint32_t stride, uint32_t count)
	{
		vBuffer = std::make_shared<VertexBuffer>(stride, count, data);
	}

	void Mesh::SubMesh::SetIndices(const void *data, uint32_t count)
	{
		iBuffer = std::make_shared <IndexBuffer>(count, data);
		m_indexCount = count;
	}

	uint32_t Mesh::SubMesh::GetIndexCount() const
	{
		return m_indexCount;
	}

	void Mesh::SubMesh::Bind()
	{
		vBuffer->Bind();
		iBuffer->Bind();
	}

	void Mesh::Draw(const Renderer& renderer)
	{
		for (SubMesh *sm : submeshes)
		{
			sm->Bind();
			renderer.Draw(sm->GetIndexCount());
		}
	}

	void Mesh::AddSubMesh(SubMesh *submesh)
	{
		submeshes.push_back(submesh);
	}

}