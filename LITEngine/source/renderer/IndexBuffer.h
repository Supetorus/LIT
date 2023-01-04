#pragma once
#include "core/core.h"
#include <d3d11.h>

namespace lit
{
	class IndexBuffer
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="count">The number of indices</param>
		/// <param name="buffer">A pointer to the buffer to be bound.</param>
		IndexBuffer(uint32_t count, const void *buffer);
		/// <summary>
		/// Binds the indices to be drawn.
		/// </summary>
		void Bind() const;
	private:
		wrl::ComPtr<ID3D11Buffer> m_IndexBuffer;
	};
}
