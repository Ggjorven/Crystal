#include <Crystal/Crystal.hpp>
#include <Crystal/Core/AppEntrypoint.hpp>

#include "Game/Settings.hpp"

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
	appInfo.WindowProperties.Name = s_WindowTitle;
	appInfo.WindowProperties.Width = s_WindowWidth;
	appInfo.WindowProperties.Height = s_WindowHeight;

	return new Game(appInfo);
}
//=========================================