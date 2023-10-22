#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "EditorLayer.hpp"

class Crystalizer : public Crystal::Application
{
public:
	Crystalizer(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		AddLayer(new EditorLayer());
	}

	virtual ~Crystalizer() {}
};



//=========================================
//------------Creation of App--------------
//=========================================
Crystal::Application* Crystal::CreateApplication(int argc, char* argv[])
{
	Crystal::ApplicationInfo appInfo;
	appInfo.WindowProperties.Name = s_WindowTitle;
	appInfo.WindowProperties.Width = s_WindowWidth;
	appInfo.WindowProperties.Height = s_WindowHeight;

	return new Crystalizer(appInfo);
}
//=========================================