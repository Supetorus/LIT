#include "Window.h"
#include "core/Log.h"
#include "Input.h"
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

		RECT windowRect{0, 0, m_clientSize.first, m_clientSize.second};
		DWORD style = WS_OVERLAPPEDWINDOW;
		AdjustWindowRect(&windowRect, style, FALSE);
		m_windowSize.first = windowRect.right - windowRect.left;
		m_windowSize.second = windowRect.bottom - windowRect.top;

		m_hwnd = CreateWindowEx(
			0, m_className, L"Learn Direct3D11", WS_OVERLAPPEDWINDOW, 0, 0, m_windowSize.first, m_windowSize.second, 0, 0, GetModuleHandle(NULL), this
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
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			int wasDown = 0x40000000;
			if (!(lParam & wasDown))
				Input::Instance.OnKeyPressed(static_cast<unsigned char>(wParam));
			break;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
			Input::Instance.OnKeyReleased(static_cast<unsigned char>(wParam));
			break;
		case WM_CHAR:
			Input::Instance.OnChar(static_cast<unsigned char>(wParam));
			break;

			// mouse
		case WM_MOUSEMOVE:
			POINTS pt = MAKEPOINTS(lParam);
			Input::Instance.OnMouseMove(pt.x, pt.y);
			break;

		case WM_LBUTTONDOWN:
			Input::Instance.OnMousePressed(Input::LMouse);
			break;
		case WM_RBUTTONDOWN:
			Input::Instance.OnMousePressed(Input::RMouse);
			break;
		case WM_MBUTTONDOWN:
			Input::Instance.OnMousePressed(Input::MMouse);
			break;

		case WM_LBUTTONUP:
			Input::Instance.OnMouseReleased(Input::LMouse);
			break;
		case WM_RBUTTONUP:
			Input::Instance.OnMouseReleased(Input::RMouse);
			break;
		case WM_MBUTTONUP:
			Input::Instance.OnMouseReleased(Input::MMouse);
			break;
		case WM_CREATE:
			return 0;
		case WM_DESTROY:
			m_quit = true;
			return 0;
		default:
			break;
		}
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
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