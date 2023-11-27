#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

#include "Crystal/ECS/Entity.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Renderer/Tools/SceneRenderer.hpp"
#include "Crystal/Renderer/Tools/EditorCamera.hpp"

namespace Crystal
{

	class SceneSerializer;

	enum class SceneState
	{
		None = 0, Editor, Runtime
	};

	class Scene // TODO(Jorben): Add scene's instead of everything in Project
	{
	public:
		Scene(const std::string& debugName = "") : m_DebugName(debugName) { m_EditorCamera = CreateRef<EditorCamera>(); }
		virtual ~Scene() = default;

		virtual void OnUpdate(Timestep& ts) = 0;
		virtual void OnRender() = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void AddEntity(Ref<ECS::Entity> entity) { m_Entities.emplace_back(entity); }
		virtual std::vector<Ref<ECS::Entity>>& GetEntities() { return m_Entities; }
		virtual Ref<ECS::Entity> GetEntityByUUID(uint64_t uuid);

		ECS::Storage& GetStorage() { return m_Storage; }
		std::string& GetName() { return m_DebugName; }

		void SetState(int state) { m_State = (SceneState)state; }

		void CopyStorage() { m_StorageCopy = m_Storage; }
		void ResetStorage() { m_Storage = m_StorageCopy; }

	protected:
		std::string m_DebugName;
		SceneState m_State = SceneState::None;

		ECS::Storage m_Storage;
		ECS::Storage m_StorageCopy;

		std::vector<Ref<ECS::Entity>> m_Entities;

		Ref<EditorCamera> m_EditorCamera;
		
		bool m_FirstUpdate = true;

		//Friend classes to be able to use some private members/functions
		friend class SceneSerializer;
	};

	class Scene2D : public Scene
	{
	public:
		Scene2D(const std::string& debugName = "");
		virtual ~Scene2D();

		void OnUpdate(Timestep& ts) override;
		void OnRender() override;
		void OnEvent(Event& e) override;

	private:
		void OnRenderEditor();
		void OnRenderRuntime();

	private:
		SceneRenderer2D m_Renderer;
	};

	class Scene3D : public Scene // TODO
	{
	public:
	};
}