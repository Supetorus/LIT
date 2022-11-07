#include "Shader.h"
#include "windows/win.h"
#include "DXContext.h"
#include <d3dcompiler.h>

DXGI_FORMAT GetFormatFromDesc(D3D11_SIGNATURE_PARAMETER_DESC &desc)
{
	if (desc.Mask == 1)
	{
		if (desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32_UINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32_SINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32_FLOAT;
	}
	else if (desc.Mask <= 3)
	{
		if (desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32_UINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32_SINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32_FLOAT;
	}
	else if (desc.Mask <= 7)
	{
		if (desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32B32_UINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32B32_SINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32B32_FLOAT;
	}
	else if (desc.Mask <= 15)
	{
		if (desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32B32A32_UINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32B32A32_SINT;
		else if (desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}
	return DXGI_FORMAT_UNKNOWN;
}

namespace wl
{

	Shader::Shader(const wchar_t *pPath, const wchar_t *vPath) :
		m_vPath(vPath)
	{
		loadShader(pPath, ShaderStage::Pixel);
		loadShader(vPath, ShaderStage::Vertex);
		generateInputLayout();
	}

	void Shader::Init(const wchar_t *pPath, const wchar_t *vPath)
	{
		m_vPath = vPath;
		loadShader(pPath, ShaderStage::Pixel);
		loadShader(vPath, ShaderStage::Vertex);
		generateInputLayout();
	}

	void Shader::Bind()
	{
		DXContext::Instance->m_context->VSSetShader(m_vertexShader.Get(), nullptr, 0u);
		DXContext::Instance->m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0u);
		DXContext::Instance->m_context->IASetInputLayout(m_inputLayout.Get());
	}

	//void Shader::SetLayout(D3D11_INPUT_ELEMENT_DESC layoutElements[], uint32_t numElements)
	//{
	//	wrl::ComPtr<ID3DBlob> pBlob;
	//	ASSERT_HR(
	//		D3DReadFileToBlob(m_vPath, &pBlob),
	//		"Unable to read in shader file."
	//	);

	//	ASSERT_HR(
	//		DXContext::Instance->m_device->CreateInputLayout(layoutElements, numElements, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_inputLayout),
	//		"Failed to create input layout."
	//	);
	//}

	void Shader::generateInputLayout()
	{
		//DirectX11RendererAPI &graphics = *(DirectX11RendererAPI *)RendererAPI::Get();

		//wrl::ComPtr<ID3DBlob> pBlob = ReadBlob(m_VertexShaderFile);
		wrl::ComPtr<ID3DBlob> pBlob;
		ASSERT_HR(
			D3DReadFileToBlob(m_vPath, &pBlob),
			"Unable to read in shader file."
		);

		// reflect on the shader
		ID3D11ShaderReflection *pReflector = nullptr;
		//HRESULT hr =
		ASSERT_HR(
			D3DReflect(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void **)&pReflector),
			"shader reflection failed"
		);

		// check if the reflection failed
		//if (FAILED(hr)) {
		//	DBOUT("shader reflection failed" << std::endl);
		//	return;
		//}

		// get the descriptor for the shader
		D3D11_SHADER_DESC reflectDesc;
		pReflector->GetDesc(&reflectDesc);

		uint32_t numInputParams = reflectDesc.InputParameters;
		D3D11_INPUT_ELEMENT_DESC *ied = new D3D11_INPUT_ELEMENT_DESC[numInputParams];

		for (uint32_t i = 0; i < numInputParams; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC ps;
			pReflector->GetInputParameterDesc(i, &ps);

			ied[i] = { ps.SemanticName, ps.SemanticIndex, GetFormatFromDesc(ps), 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		}

		//hr = 
		ASSERT_HR(
			DXContext::Instance->m_device->CreateInputLayout(ied, numInputParams, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_inputLayout),
			"Failed to create layout from reflection"
		);

		//if (FAILED(hr)) {
		//	DBOUT("failed to create layout from reflection" << std::endl);
		//}

		delete[] ied;
	}

	//void Shader::SetLayout()
	//{
	//	D3D11_INPUT_ELEMENT_DESC elemDescs[]
	//	{
	//		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//		//{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	};

	//	SetLayout(elemDescs, 2);
	//}

	void Shader::loadShader(const wchar_t *path, ShaderStage stage)
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