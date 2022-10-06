#pragma once
#include "win.h"

namespace wl
{
	class Window
	{
	public:
		Window();
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void DoMessagePump();
		bool IsQuit() { return m_quit; };
		void Close();
	private:
		HWND m_hwnd;
		PCWSTR m_className = L"MyWindow";
		bool m_quit{0};
	};
}