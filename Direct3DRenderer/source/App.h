#pragma once

#include "windows/Window.h"
#include "utilities/GameTimer.h"
//#include "Model.h"
#include "renderer/Renderer.h"
#include "Object.h"
#include <vector>

namespace wl
{
	class Window;
	class Renderer;
	class GameTimer;
	//class Object;

	class App
	{
	public:
		App() = default;
		void Init();
		void Run();
	private:
		Window m_window;
		GameTimer m_gTimer;
		std::optional<Renderer> m_renderer;
		std::vector<Object> m_objects;
	};

}
