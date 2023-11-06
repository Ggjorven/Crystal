#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/ECS/Storage.hpp"

namespace Crystal
{

	EntityScript::EntityScript(std::filesystem::path path)
	{
		// Load the dll
	}

	EntityScript::~EntityScript()
	{
	}

	void EntityScript::SetDLL(std::filesystem::path path)
	{
		// Load the dll
	}

	void EntityScript::SetClass(const std::string& name)
	{
	}

	void EntityScript::OnCreate()
	{
	}

	void EntityScript::OnUpdate(Timestep& ts)
	{
	}

}