#pragma once

#include "DX.h"
#include "core.h"

namespace lit
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
		/// <param name="window">The window which this renderer will draw to</param>
		Renderer(const Window &window);
		/// <summary>
		/// Clears the buffer to a uniform color.
		/// </summary>
		void BeginFrame();
		/// <summary>
		/// Sets the view and projection matrices using the camera.
		/// </summary>
		void SetViewProjectionMatrix() const;
		/// <summary>
		/// Sets the model's matrix
		/// </summary>
		/// <param name="objectTransform">Position, rotation, and scale of the model.</param>
		void SetModelMatrix(const Transform &objectTransform) const;
		/// <summary>
		/// Draws using whatever resources are currently bound
		/// </summary>
		/// <param name="indexCount">The number of indices which should be drawn</param>
		void Draw(uint32_t indexCount) const;
		/// <summary>
		/// Swaps the front and back buffer.
		/// </summary>
		void EndFrame();
		/// <summary>
		/// Sets the draw mode to wireframe
		/// </summary>
		void SetModeWireframe() const;
		/// <summary>
		/// Sets the draw mode to fill.
		/// </summary>
		void SetModeFill() const;
		/// <summary>
		/// Sets the camera to be used for calculating the view projection matrix. Call this if the primary camera changes.
		/// </summary>
		void SetCamera(std::shared_ptr<Camera> newCamera);
	private:
		struct TransformMatrix
		{
			DirectX::XMMATRIX transform;
		};
		struct CameraMatrix
		{
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX viewProjection;
		};
		void bindRenderTargets() const;
		void createSwapChain();
		void createRenderTarget();
		void createDepthStencilBuffer();
		void createViewport();

		const Window &m_window;
		std::shared_ptr<Camera> m_camera;

		wrl::ComPtr<IDXGISwapChain> m_swapChain;
		wrl::ComPtr<ID3D11Texture2D> m_backBuffer;
		wrl::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
		wrl::ComPtr<ID3D11Texture2D> m_depthStencilTexture;
		wrl::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pStencil;
		D3D11_VIEWPORT m_viewport;

	};
}
