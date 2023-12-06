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

					// Check if already checked
					auto pair = std::make_pair(coll1.first, coll2.first);
					bool stop = false;
					for (auto& item : checked)
					{
						if (item == pair || (item == std::make_pair(pair.second, pair.first)))
						{
							stop = true;
							break;
						}
					}
					if (stop) continue;

					// TODO(Jorben): Use some kind of origin system
					const auto& oneAABB = colC1.AABB;
					const auto& twoAABB = colC2.AABB;

					const float oneRight = oneAABB->GetPosition().X + oneAABB->GetSize().X;
					const float twoLeft = twoAABB->GetPosition().X;

					const float oneLeft = oneAABB->GetPosition().X;
					const float twoRight = twoAABB->GetPosition().X + twoAABB->GetSize().X;

					const float oneTop = oneAABB->GetPosition().Y;
					const float twoBottom = twoAABB->GetPosition().Y + twoAABB->GetSize().Y;

					const float oneBottom = oneAABB->GetPosition().Y + oneAABB->GetSize().Y;
					const float twoTop = twoAABB->GetPosition().Y;

					if (oneRight > twoLeft && oneLeft < twoRight &&
						oneBottom > twoTop && oneTop < twoBottom)
					{
						// Collision detected
						CollisionProperties oneProperties; oneProperties.Type = CollisionProperties::CollisionType::AABB;
						CollisionProperties twoProperties; twoProperties.Type = CollisionProperties::CollisionType::AABB;

						float horizontalDistance = std::min(oneRight - twoLeft, twoRight - oneLeft);
						float verticalDistance = std::min(oneBottom - twoTop, twoBottom - oneTop);

						if (horizontalDistance < verticalDistance)
						{
							// Collision is horizontal
							// TODO(Jorben): Make collisions based on the options so left = right for the other
							if (oneRight < twoRight && oneLeft < twoLeft)
							{
								//CR_CORE_TRACE("Collision on the left side");
								oneProperties.Side = CollisionProperties::CollisionSide::Left;
								twoProperties.Side = CollisionProperties::CollisionSide::Right;
							}
							else if (oneRight > twoRight && oneLeft > twoLeft)
							{
								//CR_CORE_TRACE("Collision on the right side");
								oneProperties.Side = CollisionProperties::CollisionSide::Right;
								twoProperties.Side = CollisionProperties::CollisionSide::Left;
							}
						}
						else
						{
							// Collision is vertical
							if (oneBottom < twoBottom && oneTop < twoTop)
							{
								//CR_CORE_TRACE("Collision on the bottom side");
								oneProperties.Side = CollisionProperties::CollisionSide::Bottom;
								twoProperties.Side = CollisionProperties::CollisionSide::Top;
							}
							else if (oneBottom > twoBottom && oneTop > twoTop)
							{
								//CR_CORE_TRACE("Collision on the top side");
								oneProperties.Side = CollisionProperties::CollisionSide::Top;
								twoProperties.Side = CollisionProperties::CollisionSide::Bottom;
							}
						}

						// Call OnCollision for the one entity
						if (m_Storage.HasComponent<ECS::ScriptComponent>(coll1.first))
						{
							auto& sc = m_Storage.GetComponent<ECS::ScriptComponent>(coll1.first);
							sc.Script->OnCollision(coll2.first, twoProperties, oneProperties);
						}

						// Call OnCollision for the two entity
						if (m_Storage.HasComponent<ECS::ScriptComponent>(coll2.first))
						{
							auto& sc = m_Storage.GetComponent<ECS::ScriptComponent>(coll2.first);
							sc.Script->OnCollision(coll1.first, oneProperties, twoProperties);
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
		switch (m_State)
		{

		case SceneState::Editor:
		{
			m_EditorCamera->OnUpdate(ts);
			m_FirstUpdate = true;
			break;
		}

		case SceneState::Runtime:
		{
			for (auto& sc : m_Storage.GetComponentsMap<ECS::ScriptComponent>())
			{
				auto& scC = m_Storage.GetComponent<ECS::ScriptComponent>(sc.first);
				if (m_FirstUpdate)
				{
					scC.Script->UpdateValueFieldsValues();
					scC.Script->OnCreate();
				}
				scC.Script->OnUpdate(ts);
			}

			Scene::UpdateCollisions();

			m_FirstUpdate = false;
			m_EditorCamera->OnUpdate(ts); // TODO(Jorben): Remove and replace with runtime camera
			break;
		}

		}
	}

	void Scene2D::OnRender()
	{
		switch (m_State)
		{
		case SceneState::Editor:
			OnRenderEditor();
			break;
		case SceneState::Runtime:
			OnRenderRuntime();
			break;
		}
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
