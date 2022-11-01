#pragma once
#include "core/core.h"
#include "renderer/DX.h"

namespace wl
{
	class DXContext
	{
	public:
		static DXContext *Instance;
		static void Init();
		DXContext();
		wrl::ComPtr<ID3D11Device> m_device{};
		wrl::ComPtr<ID3D11DeviceContext> m_context{}; // immediate context
	};
}
