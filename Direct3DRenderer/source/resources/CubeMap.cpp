#include "CubeMap.h"
#include "core/core.h"
#include "renderer/DX.h"
#include "renderer/DXContext.h"
#include "windows/win.h"

namespace wl
{

	CubeMap::CubeMap(std::string path):
		m_texturePath(path)
	{
		//D3D11_TEXTURECUBE_FACE_POSITIVE_X = 0,
		//D3D11_TEXTURECUBE_FACE_NEGATIVE_X = 1,
		//D3D11_TEXTURECUBE_FACE_POSITIVE_Y = 2,
		//D3D11_TEXTURECUBE_FACE_NEGATIVE_Y = 3,
		//D3D11_TEXTURECUBE_FACE_POSITIVE_Z = 4,
		//D3D11_TEXTURECUBE_FACE_NEGATIVE_Z = 5

		faces[D3D11_TEXTURECUBE_FACE_POSITIVE_X] = ImageBuffer("cubemaps/" + path + "/posx.jpg"); // right
		faces[D3D11_TEXTURECUBE_FACE_NEGATIVE_X] = ImageBuffer("cubemaps/" + path + "/negx.jpg"); // left
		faces[D3D11_TEXTURECUBE_FACE_POSITIVE_Y] = ImageBuffer("cubemaps/" + path + "/posy.jpg"); // top
		faces[D3D11_TEXTURECUBE_FACE_NEGATIVE_Y] = ImageBuffer("cubemaps/" + path + "/negy.jpg"); // bottom
		faces[D3D11_TEXTURECUBE_FACE_POSITIVE_Z] = ImageBuffer("cubemaps/" + path + "/posz.jpg"); // front
		faces[D3D11_TEXTURECUBE_FACE_NEGATIVE_Z] = ImageBuffer("cubemaps/" + path + "/negz.jpg"); // back

		D3D11_TEXTURE2D_DESC desc{};
		desc.Width = faces[0].GetWidth();
		desc.Height = faces[0].GetHeight();
		desc.MipLevels = 1;
		desc.ArraySize = 6;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
		D3D11_SUBRESOURCE_DATA data[6];
		for (int i = 0; i < 6; i++)
		{
			data[i].pSysMem = faces[i].GetData();
			data[i].SysMemPitch = faces[i].GetPitch();
			data[i].SysMemSlicePitch = 0;
		}

		wrl::ComPtr<ID3D11Texture2D> texture;
		DXContext::Instance->m_device->CreateTexture2D(&desc, data, texture.GetAddressOf());

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;

		ASSERT_HR(
			DXContext::Instance->m_device->CreateShaderResourceView(texture.Get(), &srvDesc, m_pTextureView.GetAddressOf()),
			"Unable to create shader resource."
		);

	}
	
	void CubeMap::Bind(int slot)
	{
		DXContext::Instance->m_context->PSSetShaderResources(slot, 1, m_pTextureView.GetAddressOf());
	}

	const std::string &CubeMap::GetTexturePath() const
	{
		return m_texturePath;
	}

}