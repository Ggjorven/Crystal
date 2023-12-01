#include "crpch.h"
#include "EntityScript.hpp"

#include "Crystal/Core/UUID.hpp"

#include "Crystal/Utils/Utils.hpp"
#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Data/Project/Project.hpp"

#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

#include <imgui.h>
#include <imgui_internal.h>

namespace Crystal
{
	EntityScript::EntityScript()
	{
		//CR_CORE_TRACE("ENTITYSCRIPT");
	}

	EntityScript::~EntityScript()
	{
		//CR_CORE_TRACE("~ENTITYSCRIPT");
		m_Object.Destroy();
	}

	void EntityScript::Reload()
	{
		// Note(Jorben): For some reason reload crashed the program if 'm_Name' is not checked
		if (m_Name == "1mAT3stN4meS01tD03sntCr4shForS0m3R34s0nH3lpM3") 
			CR_CORE_TRACE("Name = {0}\n\tTo find out more information about this message look at EntityScript::Reload", m_Name);
		if (!m_Name.empty())
			LoadClass();
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
		float regionAvail = ImGui::GetContentRegionAvail().x;

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4((56.f - 42.f)/255.f, (70.f - 42.f)/255.f, (71.f - 42.f)/255.f, 1.0f));
		ImGui::BeginChild("Border", ImVec2(regionAvail, 100), true, ImGuiWindowFlags_None);
		ImGui::PopStyleColor(1);

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.06f, 0.06f, 0.06f, 1.0f));
		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 5, ImGui::GetCursorPos().y + 5));
		ImGui::BeginChild("Main", ImVec2(regionAvail - 10, 100 - 10), true, ImGuiWindowFlags_None);
		ImGui::PopStyleColor(1);

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
			if (ImGui::DragFloat(std::string(std::string(" ##") + pair.first).c_str(), &pair.second, 0.5f))
			{
				m_Object.SetFieldValue(pair.first, pair.second);
			}
		}

		ImGui::EndChild();
		ImGui::EndChild();
	}

	void EntityScript::OnCreate()
	{
		//CR_CORE_TRACE("OnCreate {0}", m_UUID);
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

	void EntityScript::LoadClass()
	{
		//CR_CORE_TRACE("LoadClass: {0}", m_Name);
		auto& assemblies = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().s_Assemblies;
		if (assemblies.size() > 0)
		{
			m_Type = assemblies[0].GetType(m_Name);

			m_Object.Destroy();
			m_Object = m_Type.CreateInstance();
			
			UpdateValueFieldsValues();

			m_ValueFields.Clean();

			m_Object.InvokeMethod("SetUUID", (uint64_t)m_UUID);
			m_Object.InvokeMethod("Init");
		}
	}

}