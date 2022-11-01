#include "Texture.h"
#include "d3d11.h"
#include "ImageBuffer.h"
#include "renderer/DXContext.h"
#include "windows/win.h"

namespace wl
{
	Texture::Texture(const ImageBuffer &image)
	{
		D3D11_TEXTURE2D_DESC textureDesc{};
		textureDesc.Width = image.GetWidth();
		textureDesc.Height = image.GetHeight();
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //possibly incorrect.
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = image.GetData();
		sd.SysMemPitch = image.GetWidth() * image.GetChannels();
		wrl::ComPtr<ID3D11Texture2D> pTexture;
		ASSERT_HR(
			DXContext::Instance->m_device->CreateTexture2D(&textureDesc, &sd, pTexture.GetAddressOf()),
			"Unable to create texture."
		);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		ASSERT_HR(
			DXContext::Instance->m_device->CreateShaderResourceView(pTexture.Get(), &srvDesc, m_pTextureView.GetAddressOf()),
			"Unable to create view to texture."
		);
	}

	void Texture::Bind(uint32_t slot) const
	{
		DXContext::Instance->m_context->PSSetShaderResources(slot, 1, m_pTextureView.GetAddressOf());
	}
}