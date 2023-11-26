#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "Editor.hpp"

class Crystalizer : public Crystal::Application
{
public:
	Crystalizer(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		AddLayer(new EditorLayer(appInfo));
		//AddLayer(new Layer2D());
		//AddLayer(new Layer3D());
		//AddLayer(new ECSLayer());
		//AddLayer(new CoralLayer(appInfo));
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

	appInfo.ArgCount = argc;
	appInfo.Args = argv;

	return new Crystalizer(appInfo);
}
//=========================================