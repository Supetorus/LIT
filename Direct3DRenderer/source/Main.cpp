#include "core/Log.h"
#include "windows/Window.h"

int main(int argc, char** argv)
{
	argc; argv;
	wl::Log::Init();

	wl::Window window;

	while (!window.IsQuit())
	{
		window.DoMessagePump();
	}

	window.Close();

	return 0;
}