#include "App.h"
#include "core/Log.h"

int main(int argc, char** argv)
{
	argc; argv;
	wl::Log::Init();
	wl::App app;
	app.Init();
	app.Run();

	return 0;
}