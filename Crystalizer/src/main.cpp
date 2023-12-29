#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "Editor.hpp"
#include "Custom.hpp"

class Crystalizer : public Crystal::Application
{
public:
	Crystalizer(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		AddLayer(new EditorLayer(appInfo));
		AddLayer(new CustomLayer(appInfo));
	}

	virtual ~Crystalizer() {}
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

	return new Crystalizer(appInfo);
}
//=========================================