#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

#include "Crystal/ECS/Entity.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Renderer/Tools/EditorCamera.hpp"

#include <vector>
#include <string>


namespace Crystal
{

	class Project
	{
	public:
		Project(const std::string& debugName = "");
		virtual ~Project();

		void OnUpdate(Timestep& ts);
		void OnRender();
		void OnEvent(Event& e);

		void AddEntity(Ref<ECS::Entity> entity) { m_Entities.emplace_back(entity); }
		std::vector<Ref<ECS::Entity>>& GetEntities() { return m_Entities; }
		Ref<ECS::Entity> GetEntityByUUID(uint64_t uuid);

		ECS::Storage& GetStorage() { return m_Storage; }
		std::string GetName() { return m_DebugName; }

		void CopyStorage();
		void ResetStorage();

		static Project* GetCurrentProject() { return s_CurrentProject; }

		enum class State
		{
			None = 0, Editor, Runtime
		};

		void SetState(State state) { m_State = state; }

	protected:
		void OnRenderRuntime();
		void OnRenderEditor();

	protected:
		std::string m_DebugName;

		ECS::Storage m_Storage;
		ECS::Storage m_StorageCopy;

		std::vector<Ref<ECS::Entity>> m_Entities;

		Ref<EditorCamera> m_EditorCamera;

		static Project* s_CurrentProject;

		bool m_FirstUpdate = true;
		State m_State = State::None;

		//Friend classes to be able to use some private members/functions
		friend class ProjectSerializer;
	};

}