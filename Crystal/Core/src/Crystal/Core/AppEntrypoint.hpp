#pragma once

extern Crystal::Application* Crystal::CreateApplication(int argc, char* argv[]);

#ifndef CR_DIST
int main(int argc, char* argv[])
{
	Crystal::Application* app = Crystal::CreateApplication(argc, argv);
	app->Run();
	delete app;
	return 0;
}

#elif defined(CR_DIST) && defined(CR_PLATFORM_WINDOWS)
#include <Windows.h>

int main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    Crystal::Application* app = Crystal::CreateApplication(argc, argv);
    app->Run();
    delete app;
    return 0;
}

#else
	#error No proper combination.
#endif