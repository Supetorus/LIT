#pragma once

#include "core/core.h"
#include "d3d11.h"
#include "directxmath.h"

namespace wl
{
	class Window;

	class Renderer
	{
	public:
		Renderer() = delete;
		Renderer(const Window &window);
		void BeginFrame();
		void Draw(uint32_t size);
		void EndFrame();
		struct Vertex
		{
			float x;
			float y;
			float z;
		};
		struct TransformMatrix
		{
			DirectX::XMMATRIX transform;
		};
		struct ColorList
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			}face_colors[6];
		};
	private:
		void bindRenderTargets();
		void createSwapChain();
		void createRenderTarget();
		void createDepthStencilBuffer();
		void createViewport();

		const Window &m_window;


		//swap chain stuff
		wrl::ComPtr<IDXGISwapChain> m_swapChain;
		wrl::ComPtr<ID3D11Texture2D> m_backBuffer;
		wrl::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
		wrl::ComPtr<ID3D11Texture2D> m_depthStencilTexture;
		wrl::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
		D3D11_VIEWPORT m_viewport;
		//wrl::ComPtr<ID3D11DepthStencilView> pDSV;
		//D3D11_TEXTURE2D_DESC m_bbDesc;
	};
}
