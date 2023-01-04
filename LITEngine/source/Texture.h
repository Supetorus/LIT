#pragma once
#include "core.h"
#include "d3d11.h"

namespace lit
{
	class ImageBuffer;

	class Texture
	{
	public:
		Texture(const ImageBuffer &image);
		void Bind(uint32_t slot) const;
	private:
		wrl::ComPtr<ID3D11ShaderResourceView> m_pTextureView;
	};

}
