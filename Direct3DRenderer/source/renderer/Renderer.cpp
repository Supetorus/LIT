#include "utilities/GameTimer.h"
#include "Renderer.h"
#include "windows/Window.h"
#include "core/Log.h"
#include "DXContext.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/Shader.h"
#include "windows/win.h"
#include "Mesh.h"
#include "directxmath.h"


#pragma comment(lib, "D3DCompiler.lib")

namespace dx = DirectX;

namespace wl
{
	Renderer::Renderer(const Window &window) : m_window(window)
	{
		DXContext::Init();
		createSwapChain();
		createRenderTarget();
		createDepthStencilBuffer();
		bindRenderTargets();
		createViewport();

//Create Z Buffer
		//Create depth stencil state
		//D3D11_DEPTH_STENCIL_DESC dsDesc{};
		//dsDesc.DepthEnable = TRUE;
		//dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		//dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		//wrl::ComPtr<ID3D11DepthStencilState> pDSState;
		//ASSERT_HR(
		//	m_device->CreateDepthStencilState(
		//		&dsDesc, &pDSState
		//	),
		//	"Unable to create depth stencil state."
		//);

		////bind depth state
		//m_context->OMSetDepthStencilState(pDSState.Get(), 1u);

		////create depth stencil texture
		//wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
		//D3D11_TEXTURE2D_DESC descDepth{};
		//// Should match swap chain size.
		//descDepth.Width = m_window.GetWindowSize().first;
		//descDepth.Height = m_window.GetWindowSize().second;
		//descDepth.MipLevels = 1u;
		//descDepth.ArraySize = 1u;
		//descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		//descDepth.SampleDesc.Count = 1u;
		//descDepth.SampleDesc.Quality = 0u;
		//descDepth.Usage = D3D11_USAGE_DEFAULT;
		//descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		//ASSERT_HR(
		//	m_device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil),
		//	"Unable to create texture for depth stencil."
		//);

		////Create view of depth stencil texture
		//D3D11_DEPTH_STENCIL_VIEW_DESC descDSV{};
		//descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		//descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//descDSV.Texture2D.MipSlice = 0u;
		//ASSERT_HR(
		//	m_device->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV),
		//	"Unable to create depth stencil view."
		//);
		//m_context->OMSetRenderTargets(1u, m_pRenderTargetView.GetAddressOf(), pDSV.Get());
//End Z Buffer

		LOG("Renderer created");
	}

	void Renderer::BeginFrame()
	{
		// Clear color.
		float color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		DXContext::Instance->m_context->ClearRenderTargetView(m_renderTargetView.Get(), color);
		// Clear depth
		DXContext::Instance->m_context->ClearDepthStencilView(m_depthStencilView.Get(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f, 0);
	}

	void Renderer::Draw(uint32_t size)
	{
		static GameTimer gt;
		gt.Tick();
		float angle = gt.TotalTime();

		// Create constant buffer for transform matrix
		const Renderer::TransformMatrix tm =
		{
			{
				dx::XMMatrixTranspose
				(
					dx::XMMatrixRotationZ(angle) *
					dx::XMMatrixRotationX(angle) *
					dx::XMMatrixTranslation(0, 0, 4) *
					dx::XMMatrixPerspectiveLH(1.0f, m_window.InverseAspectRatio(), 0.5f, 10.0f)
				)
			}
		};

		ConstantBuffer transformBuffer(sizeof(TransformMatrix), ShaderStage::Vertex);

		transformBuffer.SetData(&tm);

		DXContext::Instance->m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		transformBuffer.Bind(0);

		//Draw
		DXContext::Instance->m_context->DrawIndexed(static_cast<UINT>(size), 0u, 0);
		bindRenderTargets();
	}

	void Renderer::EndFrame()
	{
		//Present
		ASSERT_HR(m_swapChain->Present(0, 0),
			"Error presenting frame.");
	}

	void Renderer::createSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC desc;								// A struct which describes the swap chain.
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));		// Clears the memory to zero out all the values.
		desc.BufferDesc.Width = m_window.GetClientSize().first;
		desc.BufferDesc.Height = m_window.GetClientSize().second;
		desc.BufferDesc.RefreshRate.Numerator = 60;				// These were not explained in the book.
		desc.BufferDesc.RefreshRate.Denominator = 1;			// These were not explained in the book.
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;// These were not explained in the book.
		desc.Windowed = TRUE;									// Sets the initial state of full-screen mode.
		desc.BufferCount = 1;									// 1 Back buffer.
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// The pixel format of the back buffer.
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// I will be rendering to the back buffer.
		desc.SampleDesc.Count = 1;								// multisampling setting
		desc.SampleDesc.Quality = 0;							// vendor-specific flag
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				// Specify DXGI_SWAP_EFFECT_DISCARD in order to
		//	let the display driver select the most efficient
		//	presentation method.
		desc.OutputWindow = m_window.GetHandle();

		// Get the Factory used to create the ID3D11Device
		wrl::ComPtr<IDXGIDevice> dxgiDevice;
		ASSERT_HR(DXContext::Instance->m_device->QueryInterface(IID_PPV_ARGS(&dxgiDevice)), "Failed to get IDXGIDevice.");

		wrl::ComPtr<IDXGIAdapter> adapter;
		ASSERT_HR(dxgiDevice->GetParent(IID_PPV_ARGS(&adapter)), "Failed to get IDXGIAdapter.");

		wrl::ComPtr<IDXGIFactory> factory;
		ASSERT_HR(adapter->GetParent(IID_PPV_ARGS(&factory)), "Failed to get IDXGIFactory.");

		ASSERT_HR(
			factory->CreateSwapChain(
				DXContext::Instance->m_device.Get(),
				&desc,
				&m_swapChain
			), "Failed to create swap chain.");
		LOG("Swap chain created");
	}

	void Renderer::createRenderTarget()
	{
		// Get the back buffer from the swap chain
		ASSERT_HR(
			m_swapChain->GetBuffer(
				0,
				IID_PPV_ARGS(&m_backBuffer)),
			"Unable to get back buffer.");

		// Create the render target view bound to the back buffer resource.
		ASSERT_HR(
			DXContext::Instance->m_device->CreateRenderTargetView(
				m_backBuffer.Get(),
				nullptr,
				m_renderTargetView.GetAddressOf()),
			"Unable to create RenderTargetView.");

		//m_backBuffer->GetDesc(&m_bbDesc);
		LOG("Render target view created");
	}

	void Renderer::createDepthStencilBuffer()
	{
		// A depth-stencil buffer is just a particular form of ID3D11Texture2D
		//	resource, which is typically used to determine which pixels have draw priority during rasterization based on the
		//	distance of the objects in the scene from the camera.

		// Create Description of the buffer.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D32_FLOAT,
			m_window.GetClientSize().first,
			m_window.GetClientSize().second,
			1, // This depth stencil view has only one texture.
			1, // Use a single mipmap level.
			D3D11_BIND_DEPTH_STENCIL
		);
		ASSERT_HR(
			DXContext::Instance->m_device->CreateTexture2D(
				&depthStencilDesc,
				nullptr,
				&m_depthStencilTexture),
			"Failed to create depth/stencil buffer.");
		// Create view to the depth stencil texture.
		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		ASSERT_HR(
			DXContext::Instance->m_device->CreateDepthStencilView(
				m_depthStencilTexture.Get(),
				0, //"Because we specified the type of our depth/stencil buffer, we specify null for this parameter."
				&m_depthStencilView),
			"Failed to create depth/stencil view");
		LOG("Depth/stencil buffer created");
	}

	void Renderer::bindRenderTargets()
	{
		DXContext::Instance->m_context->OMSetRenderTargets(
			1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	}

	void Renderer::createViewport()
	{
		ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
		m_viewport.Width = static_cast<float>(m_window.GetClientSize().first);
		m_viewport.Height = static_cast<float>(m_window.GetClientSize().second);
		m_viewport.MinDepth = 0;
		m_viewport.MaxDepth = 1;
		DXContext::Instance->m_context->RSSetViewports(
			1, // More than 1 can be used for advanced effects.
			&m_viewport
		);
	}
}