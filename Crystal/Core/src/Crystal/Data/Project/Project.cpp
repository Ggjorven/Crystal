#include "crpch.h"
#include "Project.hpp"

namespace Crystal
{

	Project::Project(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Project::~Project()
	{
	}

	void Project::OnUpdate(Timestep& ts)
	{
	}

	void Project::OnRenderRuntime()
	{
	}

	void Project::OnRenderEditor()
	{
	}

	void Project::OnEvent(Event& e)
	{
	}

}