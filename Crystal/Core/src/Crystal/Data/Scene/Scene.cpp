#include "crpch.h"
#include "Scene.hpp"

#include "SceneSerializer.hpp"
#include "Scene.hpp"

namespace Crystal
{

	Scene::Scene(const std::string& debugName) 
		: m_DebugName(debugName), m_SceneID(UUIDGenerator::GenerateUUID())
	{
		m_EditorCamera = CreateRef<EditorCamera>();
	}

	void Scene::UpdateCollisions()
	{
		// TODO(Jorben): Make collisions more efficient
		std::vector<std::pair<CR_UUID, CR_UUID>> checked = { };

		for (auto& coll1 : m_Storage.GetComponentsMap<ECS::ColliderComponent>())
		{
			for (auto& coll2 : m_Storage.GetComponentsMap<ECS::ColliderComponent>())
			{
				if ((coll1.first == coll2.first))
					continue;

				auto& colC1 = m_Storage.GetComponent<ECS::ColliderComponent>(coll1.first);
				auto& colC2 = m_Storage.GetComponent<ECS::ColliderComponent>(coll2.first);
				// AABB
				if (colC1.AABB && colC2.AABB)
				{
					UpdateAABB(coll1.first);
					UpdateAABB(coll2.first);

					ECS::ColliderComponent* smallest = nullptr;
					ECS::ColliderComponent* other = nullptr;
					CR_UUID smallID = 0;
					CR_UUID otherID = 0;

					if (colC1.AABB->GetPosition().X < colC2.AABB->GetPosition().X)
					{
						smallest = &colC1; other = &colC2;
						smallID = coll1.first; otherID = coll2.first;
					}
					else
					{
						smallest = &colC2; other = &colC1;
						smallID = coll2.first; otherID = coll1.first;
					}

					// Check if already checked
					auto pair = std::make_pair(smallID, otherID);
					bool stop = false;
					for (auto& item : checked)
					{
						if (item == pair)
						{
							stop = true;
							break;
						}
					}
					if (stop) continue;

					// TODO(Jorben): Use some kind of origin system
					if (smallest->AABB->GetPosition().X + smallest->AABB->GetSize().X > other->AABB->GetPosition().X)
					{
						if (!(smallest->AABB->GetPosition().Y + smallest->AABB->GetSize().Y <= other->AABB->GetPosition().Y) && !(other->AABB->GetPosition().Y + other->AABB->GetSize().Y <= smallest->AABB->GetPosition().Y)) 
						{
							CR_CORE_TRACE("Collision");
						}
					}

					checked.push_back(pair);
				
				}
			}
		}
	}

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

	void Scene::UpdateAABB(CR_UUID uuid)
	{
		auto& col = m_Storage.GetComponent<ECS::ColliderComponent>(uuid);
		if (m_Storage.HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& transform = m_Storage.GetComponent<ECS::TransformComponent>(uuid);

			if (col.AABB->LinkedPosition())
				col.AABB->SetPosition(transform.Position);

			if (col.AABB->LinkedSize())
				col.AABB->SetSize(transform.Size);
		}
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
			if (!m_FirstUpdate) Scene::UpdateCollisions();

			for (auto& sc : m_Storage.GetComponentsMap<ECS::ScriptComponent>())
			{
				//CR_CORE_TRACE("{0}", sc.first);
				auto& scC = m_Storage.GetComponent<ECS::ScriptComponent>(sc.first);
				if (m_FirstUpdate)
				{
					scC.Script->UpdateValueFieldsValues();
					scC.Script->OnCreate();
				}
				scC.Script->OnUpdate(ts);
			}
			m_FirstUpdate = false;
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
		m_EditorCamera->OnEvent(e);
	}

	void Scene2D::SaveScene()
	{
		SceneSerializer serializer((Scene*)this);
		serializer.Serialize(m_Properties.Path);
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
