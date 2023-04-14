#pragma once
#include "core.h"
#include "DX.h"

namespace lit
{
	class DXContext
	{
	public:
		static DXContext *Instance;
		static void Init();
		DXContext();
		wrl::ComPtr<ID3D11Device> m_device{};
		wrl::ComPtr<ID3D11DeviceContext> m_context{};
	};
}