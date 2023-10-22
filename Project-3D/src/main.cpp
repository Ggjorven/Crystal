#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "GameLayer.hpp"

class Game : public Crystal::Application
{
public:
	Game(Crystal::ApplicationInfo appInfo)
		: Application(appInfo)
	{
		AddLayer(new GameLayer());
	}

	virtual ~Game() {}
};



//=========================================
//------------Creation of App--------------
//=========================================
Crystal::Application* Crystal::CreateApplication(int argc, char* argv[])
{
	Crystal::ApplicationInfo appInfo;
	appInfo.WindowProperties.Name = "3D Project";
	appInfo.WindowProperties.Width = 1280u;
	appInfo.WindowProperties.Height = 720u;

	return new Game(appInfo);
}
//=========================================