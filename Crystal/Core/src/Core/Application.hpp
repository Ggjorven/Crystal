#pragma once

namespace Crystal
{

	class Application
	{
	public:
		Application() {}
		virtual ~Application() {}

		void Run() { while (true); }
	};

	Application* CreateApplication(int argc, char* argv[]);
}