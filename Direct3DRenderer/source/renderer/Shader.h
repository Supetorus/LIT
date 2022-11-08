#pragma once
#include "core/core.h"
#include "d3d11.h"
#include <filesystem>
#include "renderer/DX.h"
#include "DirectXMath.h"

namespace wl
{
	enum class ShaderStage
	{
		Vertex,
		Pixel
	};

	class Shader
	{
	public:
		Shader(	const wchar_t *pPath = L"shaders/PixelShader.cso",
				const wchar_t *vPath = L"shaders/VertexShader.cso");
		void Init(const wchar_t *pPath, const wchar_t *vPath);
		void Bind();
	private:
		void generateInputLayout();
		void loadShader(const wchar_t *path, ShaderStage stage);
		wrl::ComPtr<ID3D11PixelShader> m_pixelShader;
		wrl::ComPtr<ID3D11VertexShader> m_vertexShader;
		wrl::ComPtr<ID3D11InputLayout> m_inputLayout;
		const wchar_t *m_vPath;
	};
}