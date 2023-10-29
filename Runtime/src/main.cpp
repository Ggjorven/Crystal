#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "RuntimeLayer.hpp"

using namespace Crystal;

class Runtime : public Application
{
public:
	Runtime(ApplicationInfo& info)
		: Application(info)
	{
		AddLayer(new Crystal::RuntimeLayer());
	}
	~Runtime()
	{

	}
};

//=========================================
//------------Creation of App--------------
//=========================================
Crystal::Application* Crystal::CreateApplication(int argc, char* argv[])
{
	Crystal::ApplicationInfo appInfo;
	appInfo.WindowProperties.Name = "Runtime";
	appInfo.WindowProperties.Width = 1280;
	appInfo.WindowProperties.Height = 720;

	appInfo.ArgCount = argc;
	appInfo.Args = argv;

	return new Runtime(appInfo);
}
//=========================================