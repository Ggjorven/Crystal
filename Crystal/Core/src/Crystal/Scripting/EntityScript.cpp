#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/Utils/Utils.hpp"
#include "Crystal/ECS/Storage.hpp"

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
		if (m_Assembly.GetLoadStatus() != Coral::AssemblyLoadStatus::Success)
		{
			CR_CORE_WARN("Tried to load a class before specifying file or failed to load file.");
			return;
		}

		m_Name = name;
	}

	void EntityScript::OnCreate()
	{
		if (!m_Set)
		{
			m_Type = m_Assembly.GetType(m_Name);
			m_Object = m_Type.CreateInstance();
			m_Set = true;
		}
		m_Object.InvokeMethod("OnCreate");
	}

	void EntityScript::OnUpdate(Timestep& ts)
	{
		if (!m_Set)
		{
			m_Type = m_Assembly.GetType(m_Name);
			m_Object = m_Type.CreateInstance();
			m_Set = true;
		}
		m_Object.InvokeMethod("OnUpdate", (float)ts);
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

	}

}