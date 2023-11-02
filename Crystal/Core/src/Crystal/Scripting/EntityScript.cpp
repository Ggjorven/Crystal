#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/ECS/Storage.hpp"

namespace Crystal
{

	EntityScript::EntityScript(std::filesystem::path path)
	{
		// Load the dll
		m_Assembly = mono_domain_assembly_open(ECS::Storage::s_ScriptingDomain, path.generic_u8string().c_str());

		m_Image = mono_assembly_get_image(m_Assembly);
	}

	EntityScript::~EntityScript()
	{
	}

	void EntityScript::SetDLL(std::filesystem::path path)
	{
		// Load the dll
		m_Assembly = mono_domain_assembly_open(ECS::Storage::s_ScriptingDomain, path.generic_u8string().c_str());

		m_Image = mono_assembly_get_image(m_Assembly);
	}

	void EntityScript::SetClass(const std::string& name)
	{
		m_Class = mono_class_from_name(m_Image, "", name.c_str());

		m_OnCreateMethod = mono_class_get_method_from_name(m_Class, "OnCreate", 0);
		m_OnUpdateMethod = mono_class_get_method_from_name(m_Class, "OnUpdate", 1);
	}

	void EntityScript::OnCreate()
	{
		m_EntityObject = mono_object_new(ECS::Storage::s_ScriptingDomain, m_Class);
		mono_runtime_object_init(m_EntityObject);

		mono_runtime_invoke(m_OnCreateMethod, m_EntityObject, nullptr, nullptr);

	}

	void EntityScript::OnUpdate(Timestep& ts)
	{
		void* args[1] = { &ts };

		mono_runtime_invoke(m_OnUpdateMethod, m_EntityObject, args, nullptr);
	}

}