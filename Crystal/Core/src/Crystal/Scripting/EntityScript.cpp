#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/Core/UUID.hpp"

#include "Crystal/Utils/Utils.hpp"
#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

#include <imgui.h>

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

	void EntityScript::Reload()
	{
		SetDLL(m_Path);
	}

	void EntityScript::SetDLL(std::filesystem::path path)
	{
		m_Path = path;
		Load(path);
	}

	void EntityScript::SetClass(const std::string& name)
	{
		m_Name = name;

		if (!m_Name.empty())
			LoadClass();
	}

	void EntityScript::UpdateValueFieldsValues()
	{
		// TODO(Jorben): Add all types.
		for (std::pair<std::string, float>& pair : m_ValueFields.Floats)
		{
			m_Object.SetFieldValue(pair.first, pair.second);
		}
	}

	void EntityScript::DisplayValueFields()
	{
		// TODO(Jorben): Add all types.
		for (std::pair<std::string, float>& pair : m_ValueFields.Floats)
		{
			ImGui::Text(std::string(pair.first + std::string(":")).c_str());
			ImGui::SameLine();
			ImGui::DragFloat(std::string(std::string("##") + pair.first).c_str(), &pair.second, 0.5f);
		}
	}

	void EntityScript::OnCreate()
	{
		//--Components--
		if (m_Components.TagComponent)
			m_Object.InvokeMethod("AddTagComponent");

		if (m_Components.TransformComponent)
			m_Object.InvokeMethod("AddTransformComponent");

		m_Object.InvokeMethod("OnCreate");

	}

	void EntityScript::OnUpdate(Timestep& ts)
	{
		m_Object.InvokeMethod("OnUpdate", (float)ts);
	}

	void EntityScript::Load(std::filesystem::path path)
	{
		// TODO(Jorben): Make the path variable be able to be absolute instead of this fixed path
		std::string pathStr = path.string();

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

		m_Object.Destroy();
		m_Object = m_Type.CreateInstance();

		m_ValueFields.Clean();

		m_Object.InvokeMethod("SetUUID", (uint64_t)m_UUID);
		m_Object.InvokeMethod("Init");
	}

}