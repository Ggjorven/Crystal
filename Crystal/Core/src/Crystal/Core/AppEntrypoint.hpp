#pragma once

extern Crystal::Application* Crystal::CreateApplication(int argc, char* argv[]);

#if 1
int main(int argc, char* argv[])
{
	Crystal::Application* app = Crystal::CreateApplication(argc, argv);
	app->Run();
	delete app;
	return 0;
}

#else

#endif