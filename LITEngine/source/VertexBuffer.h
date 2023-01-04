#pragma once
#include "core.h"
#include <d3d11.h>

namespace lit
{
	class VertexBuffer
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="stride">The size of one vertex. Use sizeof(type) to get this.</param>
		/// <param name="count">The number of vertices in the buffer.</param>
		/// <param name="buffer">A pointer to the buffer.</param>
		VertexBuffer(uint32_t stride, uint32_t count, const void *buffer);
		/// <summary>
		/// Binds the vertices to be drawn.
		/// </summary>
		void Bind() const;
	private:
		wrl::ComPtr<ID3D11Buffer> m_VertexBuffer;
		uint32_t m_stride;
	};
}
