#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

#include "Crystal/ECS/Entity.hpp"
#include "Crystal/ECS/Storage.hpp"

#include "Crystal/Renderer/Tools/SceneRenderer.hpp"
#include "Crystal/Renderer/Tools/EditorCamera.hpp"

#include <string>
#include <filesystem>

namespace Crystal
{

	class SceneSerializer;
	class Project;

	enum class SceneState
	{
		None = 0, Editor, Runtime
	};

	struct SceneProperties
	{
	public:
		enum class Type
		{
			None = 0, _2D = 2, _3D = 3
		};

		bool operator!=(const SceneProperties& properties) const
		{
			return (Name != properties.Name || Path != properties.Path || SceneType != properties.SceneType);
		}

	public:
		std::string Name = "None";
		std::filesystem::path Path = "None";
		Type SceneType = Type::None;

	};

	class Scene
	{
	public:
		Scene(const std::string& debugName = "");
		virtual ~Scene();

		virtual void OnUpdate(Timestep& ts) = 0;
		virtual void OnRender() = 0;
		virtual void OnEvent(Event& e) = 0;

		void UpdateCollisions();

		virtual void AddEntity(Ref<ECS::Entity> entity) { m_Entities.emplace_back(entity); }
		virtual std::vector<Ref<ECS::Entity>>& GetEntities() { return m_Entities; }
		virtual Ref<ECS::Entity> GetEntityByUUID(uint64_t uuid);

		ECS::Storage& GetStorage() { return m_Storage; }
		std::string& GetName() { return m_DebugName; }
		const SceneProperties& GetProperties() { return m_Properties; }
		CR_UUID GetSceneID() const { return m_SceneID; }
		Ref<EditorCamera2D> GetEditorCamera2D() { return m_EditorCamera2D; }
		Vec4<float>& GetClearColour() { return m_ClearColour; }

		void SetProperties(const SceneProperties& properties) { m_Properties = properties; }
		void SetState(int state) { m_State = (SceneState)state; }

		void CopyStorage() { m_StorageCopy = m_Storage; }
		void ResetStorage() { m_Storage = m_StorageCopy; }

		virtual void SaveScene() = 0;

	protected:
		void UpdateAABB(CR_UUID uuid);

	protected:
		CR_UUID m_SceneID;
		std::string m_DebugName;

		SceneState m_State = SceneState::None;
		SceneProperties m_Properties;

		ECS::Storage m_Storage;
		ECS::Storage m_StorageCopy;

		std::vector<Ref<ECS::Entity>> m_Entities = { };

		Ref<EditorCamera2D> m_EditorCamera2D;
		
		bool m_FirstUpdate = true;

		Vec4<float> m_ClearColour = { 0.0f, 0.0f, 0.0f, 1.0f };

		//Friend classes to be able to use some private members/functions
		friend class Project;
		friend class SceneSerializer;
		friend class Storage;
	};

	class Scene2D : public Scene
	{
	public:
		Scene2D(const std::string& debugName = "");
		virtual ~Scene2D();

		void OnUpdate(Timestep& ts) override;
		void OnRender() override;
		void OnEvent(Event& e) override;

		void SaveScene() override;

	private:
		void OnRenderEditor();
		void OnRenderRuntime();

	private:
		SceneRenderer2D m_Renderer;
	};

	class Scene3D : public Scene // TODO
	{
	public:
		Scene3D(const std::string& debugName = "");
		virtual ~Scene3D();

		void OnUpdate(Timestep& ts) override;
		void OnRender() override;
		void OnEvent(Event& e) override;

		void SaveScene() override;

	private:
		void OnRenderEditor();
		void OnRenderRuntime();

	private:
		SceneRenderer3D m_Renderer;
		Ref<EditorCamera3D> m_EditorCamera3D;
	};
}