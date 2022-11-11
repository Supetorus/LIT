#pragma once

#include "renderer/DX.h"
#include "core/core.h"

namespace wl
{
	class Window;
	class Object;
	class Model;
	class Transform;
	class Camera;

	class Renderer
	{
	public:
		Renderer() = delete;
		Renderer(const Window &window);
		void BeginFrame();
		//void SetViewProjectionMatrix(const Transform &cameraTransform) const;
		void SetViewProjectionMatrix() const;
		void SetObjectMatrix(const Transform &objectTransform) const;
		void Draw(uint32_t indexCount) const;
		void EndFrame();
		void SetModeWireframe() const;
		void SetModeFill() const;
		void SetCamera(std::shared_ptr<Camera> newCamera);
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
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pStencil;
		D3D11_VIEWPORT m_viewport;
		std::shared_ptr<Camera> m_camera;
	};
}
