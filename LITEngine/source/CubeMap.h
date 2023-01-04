#pragma once
#include "ImageBuffer.h"
#include "DX.h"
#include "core.h"
#include <string>
#include "Shader.h"
#include "Mesh.h"

namespace lit
{

	class CubeMap
	{
	public:
		CubeMap(std::string texturePath);
		void Bind(int slot = 0);
		ImageBuffer faces[6];
		wrl::ComPtr<ID3D11ShaderResourceView> m_pTextureView;
		const std::string &GetTexturePath() const;
	private:
		std::string m_texturePath{};
	};

}
