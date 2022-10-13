#pragma once
#include "win.h"
#include <utility>

namespace wl
{
	class Window
	{
	public:
		Window();
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void DoMessagePump();
		bool IsQuit() const { return m_quit; }
		void Close();
		HWND GetHandle() const { return m_hwnd; }
		std::pair<int, int> GetClientSize() const { return m_clientSize; }
		std::pair<int, int> GetWindowSize() const { return m_windowSize; }
	private:
		HWND m_hwnd;
		PCWSTR m_className = L"MyWindow";
		bool m_quit{ 0 };
		std::pair<int, int> m_clientSize{ 800, 600 };
		std::pair<int, int> m_windowSize{ };
	};
}