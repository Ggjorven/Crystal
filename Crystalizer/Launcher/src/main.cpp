#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "LaunchMenu.hpp"

class Launcher : public Crystal::Application
{
public:
	Launcher(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		AddLayer(new LaunchMenu());
	}

	virtual ~Launcher() {}
};



//=========================================
//------------Creation of App--------------
//=========================================
Crystal::Application* Crystal::CreateApplication(int argc, char* argv[])
{
	Crystal::ApplicationInfo appInfo;
	appInfo.WindowProperties.Name = "Crystal Launcher";

	appInfo.WindowProperties.Width = 500;
	appInfo.WindowProperties.Height = 350;

	appInfo.WindowProperties.Decoration = false;

	appInfo.WindowProperties.CustomPos = true;
	appInfo.WindowProperties.X = (uint32_t)(Utils::GetDisplaySize().x / 2.0f - (float)appInfo.WindowProperties.Width / 2.0f);
	appInfo.WindowProperties.Y = (uint32_t)(Utils::GetDisplaySize().y / 2.0f - (float)appInfo.WindowProperties.Height / 2.0f);

	appInfo.ArgCount = argc;
	appInfo.Args = argv;

	return new Launcher(appInfo);
}
//=========================================