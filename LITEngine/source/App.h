#pragma once

#include "windows/Window.h"
#include "utilities/GameTimer.h"
#include <memory>

namespace lit
{
	class Window;
	class Renderer;
	class Scene;
	class GameTimer;
	class Input;

	class App
	{
	public:
		App();
		void Run();
	private:
		Window m_window;
		GameTimer m_gTimer;
		std::shared_ptr<Renderer> m_renderer;
		std::shared_ptr<Scene> m_scene;
	};

}
