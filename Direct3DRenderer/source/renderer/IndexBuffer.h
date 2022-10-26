#pragma once
#include "core/core.h"
#include <d3d11.h>

namespace wl
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t count, const void *buffer);
		void Bind() const;
	private:
		wrl::ComPtr<ID3D11Buffer> m_IndexBuffer;
	};
}
