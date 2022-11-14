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
	class Scene;
	class GameTimer;
	class Input;

	class App
	{
	public:
		App() = default;
		~App();
		void Init();
		void Run();
	private:
		Window m_window;
		GameTimer m_gTimer;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<Scene> m_scene;
		//std::vector<Model*> m_models{};
	};

}
