#include "core/Log.h"
#include "windows/Window.h"
#include "utilities/GameTimer.h"
#include <Renderer.h>

int main(int argc, char** argv)
{
	argc; argv;
	wl::Log::Init();

	wl::Window window;
	wl::Renderer renderer(window);
	wl::GameTimer timer;

	timer.Reset();

	while (!window.IsQuit())
	{
		window.DoMessagePump();
		timer.Tick();
		//UpdateScene(timer.DeltaTime());
		renderer.RenderFrame();
	}

	window.Close();

	return 0;
}