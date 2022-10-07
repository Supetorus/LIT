#include "Renderer.h"
#include "windows/Window.h"
#include "core/Log.h"
#include <WinUser.h>
#include <wrl.h>

namespace wl
{
	Renderer::Renderer(const Window &window)
	{
		createDevice();
		createSwapChain(window);
		createRenderTarget();
		createDepthStencilBuffer();
		createViewport();

LOG("Renderer created");
	}

	void Renderer::createDevice()
	{
		D3D_FEATURE_LEVEL levels[] = {
				D3D_FEATURE_LEVEL_9_1,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_11_1
		};
		// This flag adds support for surfaces with a color-channel ordering different
		// from the API default. It is required for compatibility with Direct2D.
		UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		// Create the Direct3D 11 API device object and a corresponding context.
		wrl::ComPtr<ID3D11Device> device;
		wrl::ComPtr<ID3D11DeviceContext> context;
		HRESULT hr = D3D11CreateDevice(
			nullptr, // Specify nullptr to use the default adapter.
			D3D_DRIVER_TYPE_HARDWARE, // Create a device using the hardware graphics driver.
			0, // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			deviceFlags, // Set debug and Direct2D compatibility flags.
			levels, // List of feature levels this app can support.
			ARRAYSIZE(levels), // Size of the list above.
			D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION for Windows Store apps.
			&device, // Returns the Direct3D device created.
			&m_featureLevel, // Returns feature level of device created.
			&context // Returns the device immediate context.
		);
		if (FAILED(hr))
		{
			// Handle device interface creation failure if it occurs.
			// For example, reduce the feature level requirement, or fail over
			// to WARP rendering.
			LOG("Failed to create device.");
		}
		// Store pointers to the Direct3D 11.1 API device and immediate context.
		device.As(&m_device);
		context.As(&m_deviceContext);
		LOG("Renderer started");
	}

	void Renderer::createSwapChain(const Window &window)
	{
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
		desc.Windowed = TRUE; // Sets the initial state of full-screen mode.
		desc.BufferCount = 2;
		desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		// DXGI_USAGE_RENDER_TARGET_OUTPUT enables the underlying Direct3D resource to be used as a drawing surface
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count = 1; //multisampling setting
		desc.SampleDesc.Quality = 0; //vendor-specific flag
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		desc.OutputWindow = window.GetHWND();
		// Create the DXGI device object to use in other factories, such as Direct2D.
		//wrl::ComPtr<IDXGIDevice3> dxgiDevice;
		//m_pd3dDevice.As(&dxgiDevice);
		// Create swap chain.
		wrl::ComPtr<IDXGIAdapter> adapter;
		wrl::ComPtr<IDXGIFactory> factory;
		wrl::ComPtr<IDXGIDevice> dxgiDevice;
		m_device->QueryInterface(IID_PPV_ARGS(&dxgiDevice));
		HRESULT hr = dxgiDevice->GetAdapter(&adapter);
		if (SUCCEEDED(hr))
		{
			adapter->GetParent(IID_PPV_ARGS(&factory));
			hr = factory->CreateSwapChain(
				m_device.Get(),
				&desc,
				&m_pDXGISwapChain
			);
			LOG("Swap chain created");
		}
	}

	void Renderer::createRenderTarget()
	{
		// Get the back buffer from the swap chain
		HRESULT hr = m_pDXGISwapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(void **)&m_pBackBuffer);
		// Create the render target view bound to the back buffer resource.
		hr = m_device->CreateRenderTargetView(
			m_pBackBuffer.Get(),
			nullptr,
			m_pRenderTarget.GetAddressOf()
		);
		m_pBackBuffer->GetDesc(&m_bbDesc);
		LOG("Render target created");
	}

	void Renderer::createDepthStencilBuffer()
	{
		//A depth-stencil buffer is just a particular form of ID3D11Texture2D
		//	resource, which is typically used to determine which pixels have draw priority during rasterization based on the
		//	distance of the objects in the scene from the camera.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			static_cast<UINT> (m_bbDesc.Width),
			static_cast<UINT> (m_bbDesc.Height),
			1, // This depth stencil view has only one texture.
			1, // Use a single mipmap level.
			D3D11_BIND_DEPTH_STENCIL
		);
		m_device->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&m_pDepthStencil
		);
		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		m_device->CreateDepthStencilView(
			m_pDepthStencil.Get(),
			&depthStencilViewDesc,
			&m_pDepthStencilView
		);
		LOG("Depth stencil buffer created");
	}
	
	void Renderer::createViewport()
	{
		ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
		m_viewport.Height = (float)m_bbDesc.Height;
		m_viewport.Width = (float)m_bbDesc.Width;
		m_viewport.MinDepth = 0;
		m_viewport.MaxDepth = 1;
		m_deviceContext->RSSetViewports(
			1,
			&m_viewport
		);
	}


}