#include "crpch.h"
#include "Project.hpp"

#include "Crystal/Renderer/2D/Renderer2D.hpp"

#include "Crystal/Data/Scene/SceneSerializer.hpp"

namespace Crystal
{

	Project* Project::s_CurrentProject = nullptr;

	Project::Project(const std::string& debugName)
		: m_DebugName(debugName)
	{
		Project::SetCurrentProject(this);
	}

	Project::~Project()
	{
		// TODO(Jorben): Fix this for all scenes and shit
		if (m_Scenes.size() > 0)
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(m_ActiveScene->GetProperties().Path);
		}
	}

	void Project::OnUpdate(Timestep& ts)
	{
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

	void Project::AddScene(const SceneProperties& properties)
	{
		//CR_CORE_TRACE("AddScene");

		// TODO(Jorben): Add a way to check which type of Scene it is (2D or 3D)
		// ^ TODO(Jorben): Implement using properties.SceneType _2D or _3D
		LoadScene2D(properties);
	}

	void Project::LoadScene2D(const SceneProperties& properties)
	{
		m_ActiveScene = CreateRef<Scene2D>();
		m_ActiveScene->SetProperties(properties);

		SceneSerializer serializer(m_ActiveScene);
		serializer.Deserialize(properties.Path);
	}

	void Project::LoadScene3D(const SceneProperties& properties) // TODO
	{
		CR_CORE_ASSERT(false, "Not supported.")
		//m_ActiveScene = CreateRef<Scene3D>();

		SceneSerializer serializer(m_ActiveScene);
		serializer.Deserialize(properties.Path);
	}

}