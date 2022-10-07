#include "core/Log.h"
#include "windows/Window.h"
#include <Renderer.h>

int main(int argc, char** argv)
{
	argc; argv;
	wl::Log::Init();

	wl::Window window;
	wl::Renderer renderer(window);

	while (!window.IsQuit())
	{
		window.DoMessagePump();
	}

	window.Close();

	return 0;
}