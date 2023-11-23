#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/Core/UUID.hpp"

#include "Crystal/Utils/Utils.hpp"
#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

#include <imgui.h>
#include <imgui_internal.h>

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
		CR_CORE_TRACE("AAA");
		m_Object.Destroy();
		ECS::Storage::s_Host.UnloadAssemblyLoadContext(m_Context);
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

		if (!m_Name.empty() && m_Assembly.GetLoadStatus() == Coral::AssemblyLoadStatus::Success)
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
		float regionAvail = ImGui::GetContentRegionAvail().x;

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4((56.f - 42.f)/255.f, (70.f - 42.f)/255.f, (71.f - 42.f)/255.f, 1.0f));
		ImGui::BeginChild("Border", ImVec2(regionAvail, 100), true, ImGuiWindowFlags_None);
		ImGui::PopStyleColor(1);

		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 5, ImGui::GetCursorPos().y + 5));
		ImGui::BeginChild("Main", ImVec2(regionAvail - 10, 100 - 10), true, ImGuiWindowFlags_None);

		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + ImGui::GetCurrentWindow()->Size.x / 2.0f - 40, ImGui::GetCursorPos().y));
		ImGui::Text("Valuefields: ");

		// TODO(Jorben): Add all types.
		for (std::pair<std::string, float>& pair : m_ValueFields.Floats)
		{
			ImGui::Dummy(ImVec2(3.0f, 0.0f));
			ImGui::SameLine();
			ImGui::Text(std::string(pair.first + std::string(":")).c_str());
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150.0f);
			ImGui::DragFloat(std::string(std::string(" ##") + pair.first).c_str(), &pair.second, 0.5f);
		}

		ImGui::EndChild();
		ImGui::EndChild();
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
		{
			m_Object.Destroy();
			ECS::Storage::s_Host.UnloadAssemblyLoadContext(m_Context);
		}
		
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