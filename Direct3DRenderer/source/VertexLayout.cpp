#include "VertexLayout.h"

namespace wl
{
	void VertexLayout::SetupLayout(ID3D11Device *device, ID3D11DeviceContext *context)
	{
		D3D11_INPUT_ELEMENT_DESC descriptions[]{
			{"POSITION",					// Semantic name
				0,							// Semantic Index, used for multiple textures.
				DXGI_FORMAT_R32G32B32_FLOAT,// Data Format.
				0,							// Input Slot.
				0,							// Aligned byte offset (bytes from the beginning of the struct.
				D3D11_INPUT_PER_VERTEX_DATA,// This one.
				0							// This one.
			},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::XMFLOAT3), D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		// Todo 
		//device->CreateInputLayout(descriptions, ARRAYSIZE(descriptions), );
		//context->IASetInputLayout
	}
}
