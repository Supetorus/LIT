#include "PointLightList.h"
#include "windows/win.h"
#include "renderer/DXContext.h"

namespace wl
{
	
	PointLightList::PointLightList()
	{
		D3D11_BUFFER_DESC sbufferDesc = {  };
		sbufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		sbufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		sbufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		sbufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		sbufferDesc.ByteWidth = sizeof(PointLight) * 2;
		sbufferDesc.StructureByteStride = sizeof(PointLight);

		D3D11_SUBRESOURCE_DATA sbufferData{};
		sbufferData.pSysMem = new byte[sizeof(PointLight)]{0};

		ASSERT_HR(
			DXContext::Instance->m_device->CreateBuffer(&sbufferDesc, &sbufferData, &m_buffer),
			"Unable to create buffer."
		);

		// Make view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = 1;

		ASSERT_HR(
			DXContext::Instance->m_device->CreateShaderResourceView(m_buffer.Get(), &srvDesc, &m_view),
			"Unable to get shader resource view."
		);
	}
	
	void PointLightList::Add(PointLight& light)
	{
		m_list.push_back(light);
	}

	void PointLightList::Remove(int index)
	{
		m_list.erase(m_list.begin() + index);
	}

	PointLight *PointLightList::Get(int index)
	{
		return &m_list[index];
	}

	void PointLightList::Bind(int slot) const
	{
		if (m_list.size() == 0) return;

		D3D11_MAPPED_SUBRESOURCE msub = {};

		ASSERT_HR(
			DXContext::Instance->m_context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msub),
			"Failed to update lights."
		);

		CopyMemory(msub.pData, m_list.data(), m_list.size() * sizeof(PointLight));
		DXContext::Instance->m_context->Unmap(m_buffer.Get(), 0);

		DXContext::Instance->m_context->PSSetShaderResources(slot, 1, m_view.GetAddressOf());
	}

	size_t PointLightList::Size() const
	{
		return m_list.size();
	}

}
