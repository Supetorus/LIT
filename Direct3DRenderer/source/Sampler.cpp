#include "Sampler.h"
#include "renderer/DXContext.h"
#include "windows/win.h"

namespace wl
{

	Sampler::Sampler()
	{
		D3D11_SAMPLER_DESC sd{};
		//sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; //There are 3D textures in this world apparently.
		ASSERT_HR(
			DXContext::Instance->m_device->CreateSamplerState(&sd, m_pSampler.GetAddressOf()),
			"Unable to create Sampler state."
		);
	}

	void Sampler::Bind(uint32_t slot)
	{
		DXContext::Instance->m_context->PSSetSamplers(slot, 1, m_pSampler.GetAddressOf());
	}

}