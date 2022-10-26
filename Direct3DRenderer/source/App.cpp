#include "App.h"
#include "core/Log.h"

namespace wl
{

	void App::Init()
	{
		renderer = std::make_unique<Renderer>(window);
		timer.Reset();
		//renderer = Renderer(window);
	}

	void App::Run()
	{
		while (!window.IsQuit())
		{
			window.DoMessagePump();
			timer.Tick();
			
			renderer->BeginFrame();

			renderer->Draw();
			// Draw all objects

			//Renderer end frame

			renderer->EndFrame();
		}

		window.Close();
	}

}