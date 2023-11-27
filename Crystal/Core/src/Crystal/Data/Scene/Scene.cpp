#include "crpch.h"
#include "Scene.hpp"

namespace Crystal
{

	Ref<ECS::Entity> Scene::GetEntityByUUID(uint64_t uuid)
	{
		for (Ref<ECS::Entity>& entity : m_Entities)
		{
			if (entity->GetUUID() == uuid)
				return entity;
		}
		CR_CORE_WARN("No entity with UUID ({0}) found in current Scene...", uuid);
		return nullptr;
	}



	Scene2D::Scene2D(const std::string& debugName)
		: Scene(debugName), m_Renderer(m_Storage, m_EditorCamera->GetCamera())
	{
	}

	Scene2D::~Scene2D()
	{
	}

	void Scene2D::OnUpdate(Timestep& ts)
	{
		// TODO(Jorben): Add runtime camera
		if (m_State == SceneState::Editor)
		{
			m_EditorCamera->OnUpdate(ts);
			m_FirstUpdate = true;
		}

		else if (m_State == SceneState::Runtime)
		{
			for (Ref<ECS::Entity>& entity : m_Entities)
			{
				if (entity->HasComponent<ECS::ScriptComponent>())
				{
					auto& sc = entity->GetComponent<ECS::ScriptComponent>();
					if (m_FirstUpdate)
					{
						sc.Script->UpdateValueFieldsValues();
						sc.Script->OnCreate();
						m_FirstUpdate = false;
					}
					sc.Script->OnUpdate(ts);
				}
			}
			m_EditorCamera->OnUpdate(ts); // TODO(Jorben): Remove and replace with runtime camera
		}
	}

	void Scene2D::OnRender()
	{
		if (m_State == SceneState::Editor)
			OnRenderEditor();
		if (m_State == SceneState::Runtime)
			OnRenderRuntime();
	}

	void Scene2D::OnEvent(Event& e)
	{
	}

	void Scene2D::OnRenderEditor()
	{
		m_Renderer.RenderScene();
	}

	void Scene2D::OnRenderRuntime()
	{
		// TODO(Jorben): Add runtime kind of camera
		m_Renderer.RenderScene(m_EditorCamera->GetCamera());
	}

}