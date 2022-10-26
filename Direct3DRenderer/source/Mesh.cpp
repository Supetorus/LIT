#include "Mesh.h"

namespace wl
{

	void Mesh::SetVertices(const void *data, uint32_t stride, uint32_t count)
	{
		vBuffer = std::make_shared<VertexBuffer>(stride, count, data);
	}

	void Mesh::SetIndices(const void *data, uint32_t count)
	{
		iBuffer = std::make_shared <IndexBuffer>(count, data);
	}

	void Mesh::Bind()
	{
		vBuffer->Bind();
		iBuffer->Bind();
	}

}