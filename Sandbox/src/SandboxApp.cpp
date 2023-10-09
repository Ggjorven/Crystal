#include "Crystal.hpp"

class Sandbox : public Crystal::Application
{
public:
	Sandbox() {}
	virtual ~Sandbox() {}
};



//=========================================
// -----------Creation of App--------------
//=========================================
Crystal::Application* Crystal::CreateApplication(int argc, char* argv[])
{
	return new Sandbox();
}

#include "Core/AppEntrypoint.hpp"
//=========================================