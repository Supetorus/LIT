#pragma once
#include "core/core.h"
#include "d3d11.h"
#include <filesystem>

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
		//Shader() = default;
		Shader(	const wchar_t *pPath = L"../Assets/Shaders/PixelShader.cso",
				const wchar_t *vPath = L"../Assets/Shaders/VertexShader.cso");
		void Init(const wchar_t *pPath, const wchar_t *vPath);
		void Bind();
		void SetLayout(D3D11_INPUT_ELEMENT_DESC layoutElements[], uint32_t size);// or do vector
		void SetLayout();
	private:
		void LoadShader(const wchar_t *path, ShaderStage stage);
		wrl::ComPtr<ID3D11PixelShader> m_pixelShader;
		wrl::ComPtr<ID3D11VertexShader> m_vertexShader;
		wrl::ComPtr<ID3D11InputLayout> m_inputLayout;
		const wchar_t *m_vPath;
	};
}