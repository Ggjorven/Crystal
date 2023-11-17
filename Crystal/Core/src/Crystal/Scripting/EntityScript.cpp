#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/Core/UUID.hpp"

#include "Crystal/Utils/Utils.hpp"
#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

namespace Crystal
{
	EntityScript::EntityScript()
	{
	}
	EntityScript::EntityScript(std::filesystem::path path)
	{
		Load(path);
	}

	EntityScript::~EntityScript()
	{
		m_Object.Destroy();
	}

	void EntityScript::SetDLL(std::filesystem::path path)
	{
		m_Path = path;
		Load(path);

		if (!m_Name.empty())
			LoadClass();
	}

	void EntityScript::SetClass(const std::string& name)
	{
		m_Name = name;
		LoadClass();
	}

	void EntityScript::OnCreate()
	{
		if (!m_Set)
		{
			if (!m_Name.empty())
				LoadClass();
			else
			{
				CR_CORE_WARN("Tried to run OnCreate() without setting a valid class.");
				return;
			}
		}
		//--Components--
		if (m_Queue.TagComponent)
			m_Object.InvokeMethod("AddTagComponent");

		if (m_Queue.TransformComponent)
			m_Object.InvokeMethod("AddTransformComponent");

		m_Object.InvokeMethod("OnCreate");

	}

	void EntityScript::OnUpdate(Timestep& ts)
	{
		/*
		if (!m_Set)
		{
			if (!m_Name.empty())
				LoadClass();
			else
			{
				CR_CORE_WARN("Tried to run OnUpdate without setting a valid class.");
				return;
			}
		}
		*/
		if (ts == NULL) CR_CORE_WARN("Timestep = 0");
		m_Object.InvokeMethod("OnUpdate", (float)ts);
	}

	void EntityScript::AddTagComponent()
	{
		m_Queue.TagComponent = true;
	}

	void EntityScript::AddTransformComponent()
	{
		m_Queue.TransformComponent = true;
	}

	void EntityScript::Load(std::filesystem::path path)
	{
		// TODO(Jorben): Make the path variable be able to be absolute instead of this fixed path
		std::string pathStr = path.string();

		if (m_Set)
		{
			//m_Object.Destroy();
			m_Set = false;
		}

		if (m_ContextInitialized)
			ECS::Storage::s_Host.UnloadAssemblyLoadContext(m_Context);
		
		
		m_Context = ECS::Storage::s_Host.CreateAssemblyLoadContext(path.string() + std::to_string(UUIDGenerator::GenerateUUID())); 
		m_ContextInitialized = true;
		m_Assembly = m_Context.LoadAssembly(pathStr);

		if (!m_Name.empty())
			LoadClass();
	}

	void EntityScript::LoadClass()
	{
		m_Type = m_Assembly.GetType(m_Name);
		m_Object = m_Type.CreateInstance();

		m_Object.InvokeMethod("SetUUID", (uint64_t)m_UUID);
		m_Object.InvokeMethod("Init");

		m_Set = true;
	}

}