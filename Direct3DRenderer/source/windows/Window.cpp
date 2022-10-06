#include "Window.h"
#include "core/Log.h"
#include "winuser.h"

namespace wl
{
	Window::Window()
	{
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = Window::WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = m_className;

		RegisterClass(&wc);

		//int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int windowWidth = 800;
		int windowHeight = 600;

		m_hwnd = CreateWindowEx(
			0, m_className, L"Learn Direct3D11", WS_OVERLAPPEDWINDOW, 0, 0, windowWidth, windowHeight, 0, 0, GetModuleHandle(NULL), this
		);

		ShowWindow(m_hwnd, 1);
		LOG("Window Created");
	}

	LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window *pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
			pThis = (Window *)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CREATE:
			return 0;
		case WM_DESTROY:
			m_quit = true;
			return 0;
		default:
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}
	}

	void Window::DoMessagePump()
	{
		MSG msg = { };
		
		//while (GetMessage(&msg, NULL, 0, 0))
		while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window::Close()
	{
		LOG("Window Closing");
		PostQuitMessage(0);
	}
}