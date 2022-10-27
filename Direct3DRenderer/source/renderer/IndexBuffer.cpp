#include "IndexBuffer.h"
#include "DXContext.h"
#include "windows/win.h"

wl::IndexBuffer::IndexBuffer(uint32_t count, const void *buffer)
{
	D3D11_BUFFER_DESC ibd{};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(uint16_t) * count;
	ibd.StructureByteStride = sizeof(uint16_t);
	D3D11_SUBRESOURCE_DATA isd{};
	isd.pSysMem = buffer;
	ASSERT_HR(DXContext::Instance->m_device->CreateBuffer(&ibd, &isd, m_IndexBuffer.GetAddressOf()),
		"Failed to create index buffer.");
}
void wl::IndexBuffer::Bind() const
{
	DXContext::Instance->m_context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}
