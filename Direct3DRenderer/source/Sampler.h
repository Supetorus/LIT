#pragma once
#include "core/core.h"
#include "d3d11.h"

namespace wl
{
	class Sampler
	{
	public:
		Sampler();
		void Bind(uint32_t slot);
	private:
		wrl::ComPtr<ID3D11SamplerState> m_pSampler;
	};

}
