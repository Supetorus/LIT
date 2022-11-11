#pragma once
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/DX.h"
#include <memory>

namespace wl
{
	class Mesh
	{
	public:
		struct Vertex
		{
			dx::XMFLOAT3 Pos;
			dx::XMFLOAT2 Tex;
			dx::XMFLOAT3 Normal;
		};
		Mesh() = default;
		void SetVertices(const void *data, uint32_t stride, uint32_t count);
		void SetIndices(const void *data, uint32_t count);
		uint32_t GetIndexCount() const;
		void Bind();
		std::string name{};
	private:
		std::shared_ptr<VertexBuffer> vBuffer;
		std::shared_ptr<IndexBuffer> iBuffer;
		uint32_t m_indexCount{};
	};
}
