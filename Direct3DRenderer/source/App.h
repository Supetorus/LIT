#pragma once

#include "windows/Window.h"
#include "utilities/GameTimer.h"
#include "renderer/Renderer.h"

namespace wl
{
	class Window;
	class Renderer;
	class GameTimer;

	class App
	{
	public:
		App() = default;
		void Init();
		void Run();
	private:
		Window window;
		GameTimer timer;
		std::unique_ptr<Renderer> renderer;
	};

}
