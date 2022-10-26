#pragma once
#include "core/core.h"
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")

namespace wl
{
	class DXContext
	{
	public:
		static DXContext *Instance;
		static void Init();
		DXContext();
		wrl::ComPtr<ID3D11Device> m_device;
		wrl::ComPtr<ID3D11DeviceContext> m_context; // immediate context
	};
}
