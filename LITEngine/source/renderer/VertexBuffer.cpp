#include "VertexBuffer.h"
#include "DXContext.h"
#include "windows/win.h"

namespace lit
{
	VertexBuffer::VertexBuffer(uint32_t stride, uint32_t count, const void *buffer) : m_stride(stride)
	{
		D3D11_BUFFER_DESC vbd{};
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.CPUAccessFlags = 0u;
		vbd.MiscFlags = 0u;
		vbd.ByteWidth = stride * count;
		vbd.StructureByteStride = stride;
		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = buffer;
		ASSERT_HR(DXContext::Instance->m_device->CreateBuffer(&vbd, &sd, m_VertexBuffer.GetAddressOf()), "Failed to create vertex buffer.");
	}

	void VertexBuffer::Bind() const
	{
		uint32_t zero = 0;
		DXContext::Instance->m_context->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &m_stride, &zero);
	}
}
