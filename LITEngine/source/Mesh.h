#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DX.h"
#include <memory>

namespace lit
{
	class Renderer;

	class Mesh
	{
	public:
		struct Vertex
		{
			dx::XMFLOAT3 Pos;
			dx::XMFLOAT2 Tex;
			dx::XMFLOAT3 Normal;
		};
		class SubMesh
		{
		public:
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
		Mesh() = default;
		void Draw(const Renderer& renderer);
		void AddSubMesh(SubMesh *submesh);
	private:
		std::vector<SubMesh*> submeshes{};
	};
}
