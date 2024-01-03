#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "CustomLayer.hpp"

class Sandbox : public Crystal::Application
{
public:
	Sandbox(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		AddLayer(new CustomLayer(appInfo));
	}

	virtual ~Sandbox() {}
};



//=========================================
//------------Creation of App--------------
//=========================================
Crystal::Application* Crystal::CreateApplication(int argc, char* argv[])
{
	Crystal::ApplicationInfo appInfo;
	appInfo.WindowProperties.Name = "Window";
	appInfo.WindowProperties.Width = 1280;
	appInfo.WindowProperties.Height = 720;
	appInfo.WindowProperties.VSync = false;

	appInfo.ArgCount = argc;
	appInfo.Args = argv;

	return new Sandbox(appInfo);
}
//=========================================