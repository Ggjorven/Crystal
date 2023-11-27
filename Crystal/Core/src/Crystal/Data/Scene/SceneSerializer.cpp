#include "crpch.h"
#include "SceneSerializer.hpp"

#include "Crystal/Utils/YamlUtils.hpp"

namespace Crystal
{

	SceneSerializer::SceneSerializer(Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	SceneSerializer::~SceneSerializer()
	{
	}

	void SceneSerializer::Serialize(std::filesystem::path path)
	{
		YAML::Emitter data;

		data << YAML::BeginMap;
		data << YAML::Key << "Scene";
		data << YAML::Value << m_Scene->GetName();

		data << YAML::Key << "Entities";
		data << YAML::Value << YAML::BeginSeq;

		for (Ref<ECS::Entity>& entity : m_Scene->m_Entities)
			SerializeEntity(data, entity);

		data << YAML::EndSeq;
		data << YAML::EndMap;

		std::ofstream file(path);

		if (file.good())
		{
			CR_CORE_TRACE("Adding data to file {0}: \n{1}", path.string(), data.c_str());
			file << data.c_str();
			file.close();
		}
		else
			CR_CORE_ERROR("Failed to open file {0}", path.string());
	}

	void SceneSerializer::Deserialize(std::filesystem::path path)
	{
		CR_CORE_TRACE("Loading scene: {0}", path.string());

		YAML::Node data = YAML::LoadFile(path.string());

		//Set scene name
		if (data["Scene"])
			m_Scene->m_DebugName = data["Scene"].as<std::string>();
		else
			CR_CORE_WARN("No \"Project:\" tab found in {0}\n\tNot critical, just no data loaded and starting as a blank project.", path.string());

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
				DeserializeEntity(entity);
		}

		std::stringstream ss;
		ss << data;
	}

	SceneSerializer& SceneSerializer::operator=(const SceneSerializer& other)
	{
		if (this != &other)
			m_Scene = other.m_Scene;

		return *this;
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& emitter, Ref<ECS::Entity>& entity)
	{
		CR_UUID uuid = entity->GetUUID();

		emitter << YAML::BeginMap; // Entity
		emitter << YAML::Key << "Entity";
		emitter << YAML::Value << uuid;

		if (entity->HasComponent<ECS::TagComponent>())
		{
			auto& tagC = entity->GetComponent<ECS::TagComponent>();
			emitter << YAML::Key << "TagComponent";
			emitter << YAML::BeginMap; // TagComponent

			emitter << YAML::Key << "Tag" << YAML::Value << tagC.Tag;

			emitter << YAML::EndMap; // TagComponent
		}

		if (entity->HasComponent<ECS::TransformComponent>())
		{
			auto& transform = entity->GetComponent<ECS::TransformComponent>();
			emitter << YAML::Key << "TransformComponent";
			emitter << YAML::BeginMap; // TransformComponent

			emitter << YAML::Key << "Position" << transform.Position;
			emitter << YAML::Key << "Size" << YAML::Value << transform.Size;
			emitter << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;

			emitter << YAML::EndMap; // TransformComponent
		}

		if (entity->HasComponent<ECS::Renderer2DComponent>())
		{
			auto& r2d = entity->GetComponent<ECS::Renderer2DComponent>();
			emitter << YAML::Key << "Renderer2DComponent";
			emitter << YAML::BeginMap; // Renderer2DComponent

			emitter << YAML::Key << "Enable" << r2d.Enable;
			if (r2d.Texture)
				emitter << YAML::Key << "Texture" << r2d.Texture->GetPath();
			emitter << YAML::Key << "Colour" << r2d.Colour;
			emitter << YAML::Key << "UseTexture" << r2d.UseTexture;
			emitter << YAML::Key << "UseColour" << r2d.UseColour;

			emitter << YAML::EndMap; // Renderer2DComponent
		}

		if (entity->HasComponent<ECS::ColliderComponent>())
		{
			auto& cc = entity->GetComponent<ECS::ColliderComponent>();
			emitter << YAML::Key << "ColliderComponent";
			emitter << YAML::BeginMap; // ColliderComponent

			emitter << YAML::Key << "AABB" << (cc.AABB ? true : false);

			emitter << YAML::EndMap; // ColliderComponent
		}

		if (entity->HasComponent<ECS::ScriptComponent>())
		{
			auto& sc = entity->GetComponent<ECS::ScriptComponent>();
			emitter << YAML::Key << "ScriptComponent";
			emitter << YAML::BeginMap; // Renderer2DComponent

			emitter << YAML::Key << "Path" << sc.Path.string();
			emitter << YAML::Key << "Class" << sc.Script->GetClass();

			emitter << YAML::EndMap; // Renderer2DComponent
		}

		emitter << YAML::EndMap; //Entity
	}

	void SceneSerializer::DeserializeEntity(YAML::detail::iterator_value& node)
	{
		uint64_t uuid = node["Entity"].as<uint64_t>();

		//Creation of the Entity
		Ref<ECS::Entity> entity = ECS::Entity::Create(m_Scene->m_Storage);
		entity->SetUUID(uuid);
		m_Scene->AddEntity(entity);

		//TagComponent
		auto tagComponent = node["TagComponent"];
		if (tagComponent)
		{
			ECS::TagComponent& tag = entity->AddComponent<ECS::TagComponent>();

			//ggjorven here
			tag.Tag = tagComponent["Tag"].as<std::string>();
		}

		//TransformComponent
		auto transformComponent = node["TransformComponent"];
		if (transformComponent)
		{
			ECS::TransformComponent& transform = entity->AddComponent<ECS::TransformComponent>();

			transform.Position = transformComponent["Position"].as<glm::vec3>();
			transform.Size = transformComponent["Size"].as<glm::vec3>();
			transform.Rotation = transformComponent["Rotation"].as<float>();
		}

		//Renderer2DComponent
		auto renderer2DComponent = node["Renderer2DComponent"];
		if (renderer2DComponent)
		{
			ECS::Renderer2DComponent& r2d = entity->AddComponent<ECS::Renderer2DComponent>();

			r2d.Enable = renderer2DComponent["Enable"].as<bool>();
			if (renderer2DComponent["Texture"])
				r2d.Texture = Texture2D::Create(renderer2DComponent["Texture"].as<std::string>());
			else
				r2d.Texture = nullptr;

			r2d.Colour = renderer2DComponent["Colour"].as<glm::vec4>();
			r2d.UseTexture = renderer2DComponent["UseTexture"].as<bool>();
			r2d.UseColour = renderer2DComponent["UseColour"].as<bool>();
		}

		//ColliderComponent
		auto colliderComponent = node["ColliderComponent"];
		if (colliderComponent)
		{
			ECS::ColliderComponent& cc = entity->AddComponent<ECS::ColliderComponent>();

			if (colliderComponent["AABB"].as<bool>()) cc.AABB = new AABBCollider();
		}

		//ScriptComponent
		auto scriptComponent = node["ScriptComponent"];
		if (scriptComponent)
		{
			ECS::ScriptComponent& sc = entity->AddComponent<ECS::ScriptComponent>();

			sc.Path = scriptComponent["Path"].as<std::string>();
			sc.Script->SetUUID(entity->GetUUID());
			sc.Script->SetDLL(sc.Path);
			sc.Script->SetClass(scriptComponent["Class"].as<std::string>());

			//Add components
			if (tagComponent)
				sc.Script->AddTagComponent();

			if (transformComponent)
				sc.Script->AddTransformComponent();
		}
	}

}