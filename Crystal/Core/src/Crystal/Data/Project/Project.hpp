#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

#include "Crystal/ECS/Entity.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Data/Scene/Scene.hpp"

#include "Crystal/Renderer/Tools/EditorCamera.hpp"

#include <string>
#include <vector>
#include <filesystem>

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

		void AddScene(const SceneProperties& properties);

		Ref<Scene>& GetCurrentScene() { return m_ActiveScene; }

		static void SetCurrentProject(Project* project) { s_CurrentProject = project; }
		static Project* GetCurrentProject() { return s_CurrentProject; }

		std::string GetName() { return m_DebugName; }
		
		enum class State
		{
			None = 0, Editor, Runtime
		};
		
		void SetState(State state) { m_State = state; m_ActiveScene->SetState((int)state); }

		void SaveScene() { m_ActiveScene->SaveScene(); }

	private:
		void LoadScene2D(const SceneProperties& properties);
		void LoadScene3D(const SceneProperties& properties);

	private:
		std::string m_DebugName;
		
		static Project* s_CurrentProject;

		std::vector<SceneProperties> m_Scenes;
		Ref<Scene> m_ActiveScene;

		Ref<EditorCamera> m_EditorCamera;

		State m_State = State::None;

		friend class ProjectSerializer;
	};

}