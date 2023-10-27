#include "crpch.h"
#include "SceneSerializer.hpp"

#include <glm/glm.hpp>
#include "Utils/YamlUtils.hpp"

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

		for (ECS::Entity& entity : m_Scene->m_Entities)
			SerializeEntity(data, entity);

		data << YAML::EndSeq;
		data << YAML::EndMap;

		std::ofstream file(path);

		if (file.good())
		{
			//CR_CORE_TRACE("Adding data to file {0}: \n{1}", path.string(), data.c_str());
			file << data.c_str();
			file.close();
		}
		else
			CR_CORE_ERROR("Failed to open file {0}", path.string());
	}

	void SceneSerializer::Deserialize(std::filesystem::path path)
	{
		YAML::Node data = YAML::LoadFile(path.string());

		//Set scene name
		m_Scene->m_DebugName = data["Scene"].as<std::string>(); 

		auto& entities = data["Entities"];
		if (entities)
		{
			for (auto& entity : entities)
				DeserializeEntity(entity);
		}
		
		std::stringstream ss;
		ss << data;
		CR_CORE_TRACE("Loading data from file {0}: \n{1}", path.string(), ss.str());
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& emitter, ECS::Entity& entity)
	{
		CR_UUID uuid = entity.GetUUID();

		emitter << YAML::BeginMap; // Entity
		emitter << YAML::Key << "Entity";
		emitter << YAML::Value << uuid;

		if (entity.GetComponent<ECS::TagComponent>())
		{
			emitter << YAML::Key << "TagComponent";
			emitter << YAML::BeginMap; // TagComponent

			auto& tag = entity.GetComponent<ECS::TagComponent>()->Tag;
			emitter << YAML::Key << "Tag" << YAML::Value << tag;

			emitter << YAML::EndMap; // TagComponent
		}

		if (entity.GetComponent<ECS::TransformComponent>())
		{
			emitter << YAML::Key << "TransformComponent";
			emitter << YAML::BeginMap; // TransformComponent

			auto& transform = *entity.GetComponent<ECS::TransformComponent>();
			emitter << YAML::Key << "Position" << transform.Position;
			emitter << YAML::Key << "Size" << YAML::Value << transform.Size;
			emitter << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;

			emitter << YAML::EndMap; // TransformComponent
		}

		emitter << YAML::EndMap; //Entity 
	}

	void SceneSerializer::DeserializeEntity(YAML::detail::iterator_value& node)
	{
		uint64_t uuid = node["Entity"].as<uint64_t>();

		//Creation of the Entity
		ECS::Entity entity = ECS::Entity::Create(m_Scene->m_Storage);
		entity.SetUUID(uuid);

		//TagComponent
		auto tagComponent = node["TagComponent"];
		if (tagComponent)
		{
			CR_CORE_TRACE("Loaded tag component.");

			ECS::TagComponent tag;
			tag.Tag = tagComponent["Tag"].as<std::string>();

			entity.AddComponent<ECS::TagComponent>(tag);
		}

		//TransformComponent
		auto transformComponent = node["TransformComponent"];
		if (transformComponent)
		{
			CR_CORE_TRACE("Loaded transform component.");

			ECS::TransformComponent transform;
			transform.Position = transformComponent["Position"].as<glm::vec3>();
			transform.Size = transformComponent["Size"].as<glm::vec3>();
			transform.Rotation = transformComponent["Rotation"].as<float>();

			entity.AddComponent<ECS::TransformComponent>(transform);
		}

		m_Scene->AddEntity(entity);
	}

}