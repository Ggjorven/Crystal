#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "EditorLayer.hpp"
#include "FrameBufferLayer.hpp"

class Crystalizer : public Crystal::Application
{
public:
	Crystalizer(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		//AddLayer(new EditorLayer());
		AddLayer(new FramebufferLayer());
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

	return new Crystalizer(appInfo);
}
//=========================================