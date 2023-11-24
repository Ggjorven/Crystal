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

/* Note(Jorben): Use this sometime.
To draw your triangles in wireframe mode, you can configure how OpenGL draws its primitives via glPolygonMode(GL_FRONT_AND_BACK, GL_LINE). The first argument says we want to apply it to the front and back of all triangles and the second line tells us to draw them as lines. Any subsequent drawing calls will render the triangles in wireframe mode until we set it back to its default using glPolygonMode(GL_FRONT_AND_BACK, GL_FILL).
*/