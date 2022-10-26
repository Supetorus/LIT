#include "ConstantBuffer.h"
#include "windows/win.h"
#include "DXContext.h"

namespace wl
{
	
	ConstantBuffer::ConstantBuffer(uint32_t size, ShaderStage shaderStage):
		stage(shaderStage),
		size(size)
	{
		D3D11_BUFFER_DESC tbd{};
		tbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		tbd.Usage = D3D11_USAGE_DYNAMIC;
		tbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		tbd.ByteWidth = size;
		D3D11_SUBRESOURCE_DATA tsd{};
		tsd.pSysMem = new byte[size]{0};
		ASSERT_HR(DXContext::Instance->m_device->CreateBuffer(&tbd, &tsd, m_cBuffer.GetAddressOf()),
			"Unable to create transform matrix buffer.");
	}

	void ConstantBuffer::SetData(const void *data)
	{
		D3D11_MAPPED_SUBRESOURCE msub{};
		ASSERT_HR(
			DXContext::Instance->m_context->Map(m_cBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msub),
			"Unable to set data on constant buffer."
		);
		CopyMemory(msub.pData, data, size);
		DXContext::Instance->m_context->Unmap(m_cBuffer.Get(), 0);
	}

	void ConstantBuffer::Bind(uint32_t slot)
	{
		switch (stage)
		{
		case ShaderStage::Vertex:
			DXContext::Instance->m_context->VSSetConstantBuffers(slot, 1u, m_cBuffer.GetAddressOf());
			break;
		case ShaderStage::Pixel:
			DXContext::Instance->m_context->PSSetConstantBuffers(slot, 1u, m_cBuffer.GetAddressOf());
			break;
		}
	}

}