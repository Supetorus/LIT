#include "Shader.h"
#include "windows/win.h"
#include "DXContext.h"
#include <d3dcompiler.h>

namespace wl
{
	Shader::Shader(const wchar_t *pPath, const wchar_t *vPath) :
		m_vPath(vPath)
	{
		LoadShader(pPath, ShaderStage::Pixel);
		LoadShader(vPath, ShaderStage::Vertex);
	}

	void Shader::Init(const wchar_t *pPath, const wchar_t *vPath)
	{
		m_vPath = vPath;
		LoadShader(pPath, ShaderStage::Pixel);
		LoadShader(vPath, ShaderStage::Vertex);
	}

	void Shader::Bind()
	{
		DXContext::Instance->m_context->VSSetShader(m_vertexShader.Get(), nullptr, 0u);
		DXContext::Instance->m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0u);
		DXContext::Instance->m_context->IASetInputLayout(m_inputLayout.Get());
	}

	void Shader::SetLayout(D3D11_INPUT_ELEMENT_DESC layoutElements[], uint32_t numElements)
	{
		wrl::ComPtr<ID3DBlob> pBlob;
		ASSERT_HR(
			D3DReadFileToBlob(m_vPath, &pBlob),
			"Unable to read in shader file."
		);

		ASSERT_HR(
			DXContext::Instance->m_device->CreateInputLayout(layoutElements, numElements, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_inputLayout),
			"Failed to create input layout."
		);
	}

	void Shader::SetLayout()
	{
		D3D11_INPUT_ELEMENT_DESC elemDescs[]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			//{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		SetLayout(elemDescs, 2);
	}

	void Shader::LoadShader(const wchar_t *path, ShaderStage stage)
	{
		wrl::ComPtr<ID3DBlob> pBlob;
		ASSERT_HR(
			D3DReadFileToBlob(path, &pBlob),
			"Unable to read in shader file."
		);

		switch (stage)
		{
		case ShaderStage::Vertex:
			ASSERT_HR(
				DXContext::Instance->m_device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf()),
				"Unable to create vertex shader."
			);
			break;
		case ShaderStage::Pixel:
			ASSERT_HR(
				DXContext::Instance->m_device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, m_pixelShader.GetAddressOf()),
				"Unable to create Pixel Shader."
			);
			break;
		}
	}
}