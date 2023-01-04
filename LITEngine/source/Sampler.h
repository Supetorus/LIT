#pragma once
#include "core.h"
#include "d3d11.h"

namespace lit
{
	class Sampler
	{
	public:
		Sampler();
		void Bind(uint32_t slot) const;
	private:
		wrl::ComPtr<ID3D11SamplerState> m_pSampler;
	};

}
