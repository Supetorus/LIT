#pragma once

#include "core/core.h"
#include "d3d11.h"
#include "directxmath.h"

namespace wl
{
	class Window;
	class Object;
	class Model;
	class Transform;

	class Renderer
	{
	public:
		Renderer() = delete;
		Renderer(const Window &m_window);
		void BeginFrame();
		void Draw(const Model &model, const Transform &transform) const;
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
		void bindRenderTargets() const;
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
	};
}
