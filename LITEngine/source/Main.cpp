#include "App.h"
#include "Log.h"

int main(int argc, char** argv)
{
	argc; argv;

	lit::Log::Init();
	lit::App app;
	app.Run();

	return 0;
}