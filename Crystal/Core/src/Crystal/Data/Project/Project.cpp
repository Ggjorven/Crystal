#include "crpch.h"
#include "Project.hpp"

#include "Crystal/Core/Application.hpp"

#include "Crystal/Renderer/2D/Renderer2D.hpp"

#include "Crystal/Data/Scene/SceneSerializer.hpp"

namespace Crystal
{

	Project* Project::s_CurrentProject = nullptr;

	Project::Project(const std::string& debugName)
		: m_DebugName(debugName)
	{
		//CR_CORE_TRACE("Project");
		Project::SetCurrentProject(this);
	}

	Project::~Project()
	{
		m_ActiveScene.reset();
		//CR_CORE_TRACE("~Project");
	}

	void Project::OnUpdate(Timestep& ts)
	{
		if (m_SetNewScene)
		{
			SetScene(m_NewSceneProperties);
			m_SetNewScene = false;

			if (m_State == State::Runtime)
			{
				m_ActiveScene->CopyStorage();
			}
		}

		m_ActiveScene->SetState((int)m_State);
		m_ActiveScene->OnUpdate(ts);
	}

	void Project::OnRender()
	{
		m_ActiveScene->OnRender();
	}

	void Project::OnEvent(Event& e)
	{
		m_ActiveScene->OnEvent(e);
	}

	void Project::SetScene(const SceneProperties& props)
	{
		if (m_ActiveScene) 
			m_ActiveScene->GetStorage().DestroyObjects();

		switch (props.SceneType)
		{
		case SceneProperties::Type::_2D:
			LoadScene2D(props);
			break;

		case SceneProperties::Type::_3D:
			LoadScene3D(props);
			break;

		default:
			CR_CORE_WARN("No scene type selected, {0}\n\tLoading the scene as a 2D scene.", props.Path.string());
			props.SceneType = SceneProperties::Type::_2D;
			LoadScene2D(props);
			break;
		}
	}

	void Project::SetSceneBasedOnName(const std::string& name)
	{
		for (auto& props : m_Scenes)
		{
			if (props.Name == name)
			{
				m_SetNewScene = true;
				m_NewSceneProperties = props;
			}
		}
	}

	void Project::LoadScene2D(const SceneProperties& properties)
	{
		m_ActiveScene = CreateRef<Scene2D>();
		m_ActiveScene->SetProperties(properties);

		SceneSerializer serializer(m_ActiveScene);
		serializer.Deserialize(m_ProjectDir / m_SceneDir / properties.Path);
	}

	void Project::LoadScene3D(const SceneProperties& properties) // TODO
	{
		CR_CORE_ASSERT(false, "Not supported.")
		//m_ActiveScene = CreateRef<Scene3D>();

		SceneSerializer serializer(m_ActiveScene);
		serializer.Deserialize(properties.Path);
	}

}