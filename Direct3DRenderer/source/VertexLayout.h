#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
namespace wl
{
	class VertexLayout
	{
	public:
		struct Vertex
		{
			DirectX::XMFLOAT3 Position;
			DirectX::XMFLOAT4 Color;
		};
		void SetupLayout(ID3D11Device *device, ID3D11DeviceContext *context);
	};
}
