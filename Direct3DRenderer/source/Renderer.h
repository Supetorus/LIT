#pragma once

#include "core/core.h"
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")

namespace wl
{
	class Window;

	class Renderer
	{
	public:
		Renderer() = delete;
		Renderer(const Window &window);
		void bindRenderTargets();
	private:
		void createDevice();
		void createSwapChain();
		void createRenderTarget();
		void createDepthStencilBuffer();
		void createViewport();

		const Window &m_window;
		D3D_FEATURE_LEVEL m_featureLevel{}; // The feature level supported by the renderer.
		wrl::ComPtr<ID3D11Device> m_device;
		wrl::ComPtr<ID3D11DeviceContext> m_deviceContext; // immediate context
		wrl::ComPtr<IDXGISwapChain> m_pDXGISwapChain;
		wrl::ComPtr<ID3D11Texture2D> m_pBackBuffer;
		wrl::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
		D3D11_TEXTURE2D_DESC m_bbDesc;
		wrl::ComPtr<ID3D11Texture2D> m_pDepthStencil;
		wrl::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
		D3D11_VIEWPORT m_viewport;
	};
}
