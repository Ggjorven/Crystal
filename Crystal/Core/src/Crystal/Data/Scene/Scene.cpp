#include "crpch.h"
#include "Scene.hpp"

#include "Crystal/Data/Scene/SceneSerializer.hpp"
#include "Crystal/Data/Scene/Scene.hpp"

#include "Crystal/Data/Project/Project.hpp"

#include <psapi.h>
#include <iostream>

namespace Crystal
{

	Scene::Scene(const std::string& debugName) 
		: m_DebugName(debugName), m_SceneID(UUIDGenerator::GenerateUUID())
	{
		//CR_CORE_TRACE("Scene");
		m_EditorCamera2D = CreateRef<EditorCamera2D>();
	}

	Scene::~Scene()
	{
		//CR_CORE_TRACE("~Scene");
	}

	void Scene::UpdateCollisions()
	{
		// Note(Jorben): Probably not the most efficient way to check collisions
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
		: Scene(debugName), m_Renderer(m_Storage, m_EditorCamera2D->GetCamera())
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
			m_EditorCamera2D->OnUpdate(ts);
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

			// Update primary camera
			auto& camera = m_EditorCamera2D->GetCamera();

			for (auto& camC : m_Storage.GetComponentsMap<ECS::CameraComponent2D>())
			{
				auto& cam = m_Storage.GetComponent<ECS::CameraComponent2D>(camC.first);

				if (cam.Primary)
				{
					camera = cam.Camera;

					camera->SetPosition(Vec3<float>(cam.Position.x, cam.Position.y, 0.0f));
					camera->SetProjection(cam.Size.x / 2.0f * -1 * cam.Zoom, cam.Size.x / 2.0f * cam.Zoom,
						cam.Size.y / 2.0f * -1 * cam.Zoom, cam.Size.y / 2.0f * cam.Zoom);
					camera->SetRotation(cam.Rotation);
					break;
				}
			}
			// TODO(Jorben): Update editorcamera if no camera is selected
			//m_EditorCamera2D->OnUpdate(ts);

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
		m_EditorCamera2D->OnEvent(e);
	}

	void Scene2D::SaveScene()
	{
		auto proj = Project::GetCurrentProject();

		SceneSerializer serializer((Scene*)this);
		serializer.Serialize(proj->GetProjectDir() / proj->GetSceneDir() / m_Properties.Path);
	}

	void Scene2D::OnRenderEditor()
	{
		m_Renderer.RenderScene();
	}

	void Scene2D::OnRenderRuntime()
	{
		Ref<OrthoGraphicCamera> camera = m_EditorCamera2D->GetCamera();

		// TODO(Jorben): Make this loop only run once? and check for updates of camera another way?
		for (auto& camC : m_Storage.GetComponentsMap<ECS::CameraComponent2D>())
		{
			auto& cam = m_Storage.GetComponent<ECS::CameraComponent2D>(camC.first);
			//CR_CORE_TRACE("{0} Primary: {1}", camC.first, cam.Primary);
			if (cam.Primary)
			{
				camera = cam.Camera;
				break;
			}
		}

		m_Renderer.RenderScene(camera);
	}

	Scene3D::Scene3D(const std::string& debugName) // TODO(Jorben): Add Renderer2D too
		: Scene(debugName), m_EditorCamera3D(CreateRef<EditorCamera3D>()), m_Renderer(m_Storage)
	{
		m_Renderer.SetCamera(m_EditorCamera3D->GetCamera());
	}

	Scene3D::~Scene3D()
	{
	}

	void Scene3D::OnUpdate(Timestep& ts)
	{
		// TODO(Jorben): Add runtime camera
		switch (m_State)
		{

		case SceneState::Editor:
		{
			m_EditorCamera2D->OnUpdate(ts);
			m_EditorCamera3D->OnUpdate(ts);
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

			// Update primary camera
			auto& camera = m_EditorCamera3D->GetCamera();
			for (auto& camC : m_Storage.GetComponentsMap<ECS::CameraComponent3D>())
			{
				auto& cam = m_Storage.GetComponent<ECS::CameraComponent3D>(camC.first);

				if (cam.Primary)
				{
					camera = cam.Camera;

					camera->SetPosition(cam.Position);
					camera->SetAspectRatio(cam.Size.x, cam.Size.y);
					// TODO(Jorben): Make this different, 'cause I'm storing the data basically twice now
					camera->GetSettings().FOV = cam.FOV;
					camera->GetSettings().Yaw = cam.Yaw;
					camera->GetSettings().Pitch = cam.Pitch;

					camera->UpdateAll();
					break;
				}
			}
			// TODO(Jorben): Update editorcamera if no camera is selected

			break;
		}

		}
	}

	void Scene3D::OnRender()
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

	void Scene3D::OnEvent(Event& e)
	{
		m_EditorCamera2D->OnEvent(e);
		m_EditorCamera3D->OnEvent(e);
	}

	void Scene3D::SaveScene()
	{
		auto proj = Project::GetCurrentProject();

		SceneSerializer serializer((Scene*)this);
		serializer.Serialize(proj->GetProjectDir() / proj->GetSceneDir() / m_Properties.Path);
	}

	void Scene3D::OnRenderEditor()
	{
		m_Renderer.RenderScene();
	}

	void Scene3D::OnRenderRuntime()
	{
		Ref<PerspectiveCamera> camera = m_EditorCamera3D->GetCamera();

		// TODO(Jorben): Make this loop only run once? and check for updates of camera another way?
		for (auto& camC : m_Storage.GetComponentsMap<ECS::CameraComponent3D>())
		{
			auto& cam = m_Storage.GetComponent<ECS::CameraComponent3D>(camC.first);

			if (cam.Primary)
			{
				camera = cam.Camera;
				break;
			}
		}

		m_Renderer.RenderScene(camera);
	}

}
