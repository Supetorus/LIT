#include "DX.h"
#include "DXContext.h"
#include "win.h"

namespace lit
{
	DXContext *DXContext::Instance{};

	void DXContext::Init()
	{
		if (!Instance)
		{
			Instance = new DXContext();
		}
	}

	DXContext::DXContext()
	{
		// This flag adds support for surfaces with a color-channel ordering different
		// from the API default. It is required for compatibility with Direct2D.
		UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		// Create the Direct3D 11 API device object and a corresponding context.
		wrl::ComPtr<ID3D11Device> device;
		wrl::ComPtr<ID3D11DeviceContext> context;
		ASSERT_HR(
			D3D11CreateDevice(
				nullptr, // Specify nullptr to use the default adapter.
				D3D_DRIVER_TYPE_HARDWARE, // Create a device using the hardware graphics driver.
				0, // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
				deviceFlags, // Set debug and Direct2D compatibility flags.
				nullptr, // nullptr means it will target the latest available. should be 11.
				0, // Size of the list above.
				D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION for Windows Store apps.
				&device, // Returns the Direct3D device created.
				nullptr, // Returns feature level of device created (in case somebody cared).
				&context // Returns the device immediate context.
			),
			"Failed to create device."
		);
		// Store pointers to the Direct3D 11.1 API device and immediate context.
		device.As(&m_device);
		context.As(&m_context);
		LOG("Device Created.");
	}
}
