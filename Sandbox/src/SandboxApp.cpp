#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "SandboxLayer.hpp"

class Sandbox : public Crystal::Application
{
public:
	Sandbox(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		AddLayer(new SandboxLayer());
	}

	virtual ~Sandbox() {}
};



//=========================================
//------------Creation of App--------------
//=========================================
Crystal::Application* Crystal::CreateApplication(int argc, char* argv[])
{
	Crystal::ApplicationInfo appInfo;
	appInfo.WindowProperties.Name = "Window name";
	appInfo.WindowProperties.Width = 1280;
	appInfo.WindowProperties.Height = 720;

	return new Sandbox(appInfo);
}
//=========================================