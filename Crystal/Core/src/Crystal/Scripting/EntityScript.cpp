#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/Utils/Utils.hpp"
#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

namespace Crystal
{

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
		Load(path);
	}

	void EntityScript::SetClass(const std::string& name)
	{
		m_Name = name;
		if (m_Assembly.GetLoadStatus() != Coral::AssemblyLoadStatus::Success)
		{
			CR_CORE_WARN("Tried to load a class before specifying file or failed to load file.");
			return;
		}
	}

	void EntityScript::OnCreate()
	{
		if (!m_Set)
			LoadClass();

		// TagComponent
		if (m_Queue.SetTag)
		{
			m_Object.InvokeMethod("AddTagComponent", Coral::NativeString(m_Queue.Tag));

			// Reset
			m_Queue.SetTag = false;
			m_Queue.Tag = "";
		}

		m_Object.InvokeMethod("OnCreate");

	}

	void EntityScript::OnUpdate(Timestep& ts)
	{
		if (!m_Set)
			LoadClass();

		m_Object.InvokeMethod("OnUpdate", (float)ts);
	}

	void EntityScript::AddTagComponent(ECS::TagComponent& tagComponent)
	{
		CR_CORE_TRACE("(EntityScript::AddTagComponent)");
		m_Queue.SetTag = true;
		m_Queue.Tag = tagComponent.Tag;
	}

	void EntityScript::Load(std::filesystem::path path)
	{
		std::string pathStr = Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Debug-windows-x86_64\\Coral\\") + path.string();

		if (m_Set)
		{
			m_Object.Destroy();
			m_Set = false;
		}

		if (m_ContextInitialized)
			ECS::Storage::s_Host.UnloadAssemblyLoadContext(m_Context);
		
		
		m_Context = ECS::Storage::s_Host.CreateAssemblyLoadContext(path.string()); 
		m_ContextInitialized = true;
		m_Assembly = m_Context.LoadAssembly(pathStr);

		//removed setup here
	}

	void EntityScript::LoadClass()
	{
		m_Type = m_Assembly.GetType(m_Name);
		m_Object = m_Type.CreateInstance();

		// TODO(Jorben): Add the entity to the class
		//m_Object.InvokeMethod("", &m_Entity)
		m_Object.InvokeMethod("SetUUID", (uint64_t)m_UUID);

		m_Set = true;
	}

}