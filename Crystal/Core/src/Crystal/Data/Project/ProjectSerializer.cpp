#include "crpch.h"
#include "ProjectSerializer.hpp"

#include <glm/glm.hpp>
#include "Utils/YamlUtils.hpp"

namespace Crystal
{

	ProjectSerializer::ProjectSerializer(Ref<Project>& project)
		: m_Project(project)
	{
	}

	ProjectSerializer::~ProjectSerializer() = default;

	void ProjectSerializer::Serialize(std::filesystem::path path)
	{
		YAML::Emitter data;


		data << YAML::BeginMap;
		data << YAML::Key << "Project";
		data << YAML::Value << m_Project->GetName();

		data << YAML::Key << "Entities";
		data << YAML::Value << YAML::BeginSeq;

		for (ECS::Entity& entity : m_Project->m_Entities)
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

	void ProjectSerializer::Deserialize(std::filesystem::path path)
	{
		YAML::Node data = YAML::LoadFile(path.string());

		//Set scene name
		if (data["Project"])
			m_Project->m_DebugName = data["Project"].as<std::string>();
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
		CR_CORE_TRACE("Loading project: {0}", path.string());
	}

	ProjectSerializer& ProjectSerializer::operator=(const ProjectSerializer& other)
	{
		if (this != &other)
			m_Project = other.m_Project;

		return *this;
	}

	void ProjectSerializer::SerializeEntity(YAML::Emitter& emitter, ECS::Entity& entity)
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

		if (entity.GetComponent<ECS::Renderer2DComponent>())
		{
			emitter << YAML::Key << "Renderer2DComponent";
			emitter << YAML::BeginMap; // Renderer2DComponent

			auto& r2d = *entity.GetComponent<ECS::Renderer2DComponent>();
			emitter << YAML::Key << "Enable" << r2d.Enable;
			if (r2d.Texture)
				emitter << YAML::Key << "Texture" << r2d.Texture->GetPath();
			emitter << YAML::Key << "Colour" << r2d.Colour;
			emitter << YAML::Key << "UseTexture" << r2d.UseTexture;

			emitter << YAML::EndMap; // Renderer2DComponent
		}

		if (entity.GetComponent<ECS::ScriptComponent>())
		{
			emitter << YAML::Key << "ScriptComponent";
			emitter << YAML::BeginMap; // Renderer2DComponent

			auto& sc = *entity.GetComponent<ECS::ScriptComponent>();
			emitter << YAML::Key << "Path" << sc.Path.string();
			emitter << YAML::Key << "Class" << sc.Script.GetClass();

			emitter << YAML::EndMap; // Renderer2DComponent
		}

		emitter << YAML::EndMap; //Entity 
	}

	void ProjectSerializer::DeserializeEntity(YAML::detail::iterator_value& node)
	{
		uint64_t uuid = node["Entity"].as<uint64_t>();

		//Creation of the Entity
		ECS::Entity entity = ECS::Entity::Create(m_Project->m_Storage);
		entity.SetUUID(uuid);

		//TagComponent
		auto tagComponent = node["TagComponent"];
		if (tagComponent)
		{
			ECS::TagComponent tag;
			tag.Tag = tagComponent["Tag"].as<std::string>();

			entity.AddComponent<ECS::TagComponent>(tag);
		}

		//TransformComponent
		auto transformComponent = node["TransformComponent"];
		if (transformComponent)
		{
			ECS::TransformComponent transform;
			transform.Position = transformComponent["Position"].as<glm::vec3>();
			transform.Size = transformComponent["Size"].as<glm::vec3>();
			transform.Rotation = transformComponent["Rotation"].as<float>();

			entity.AddComponent<ECS::TransformComponent>(transform);
		}

		//Renderer2DComponent
		auto renderer2DComponent = node["Renderer2DComponent"];
		if (renderer2DComponent)
		{
			ECS::Renderer2DComponent r2d;
			r2d.Enable = renderer2DComponent["Enable"].as<bool>();
			if (renderer2DComponent["Texture"])
				r2d.Texture = Texture2D::Create(renderer2DComponent["Texture"].as<std::string>());

			r2d.Colour = renderer2DComponent["Colour"].as<glm::vec4>();
			r2d.UseTexture = renderer2DComponent["UseTexture"].as<bool>();

			entity.AddComponent<ECS::Renderer2DComponent>(r2d);
		}

		//ScriptComponent
		auto scriptComponent = node["ScriptComponent"];
		if (scriptComponent)
		{
			ECS::ScriptComponent sc;
			sc.Path = scriptComponent["Path"].as<std::string>();
			sc.Script.SetDLL(sc.Path);
			sc.Script.SetClass(scriptComponent["Class"].as<std::string>());
			sc.Script.SetUUID(entity.GetUUID());

			//Add components
			if (tagComponent)
				sc.Script.AddTagComponent();

			if (transformComponent)
				sc.Script.AddTransformComponent();

			entity.AddComponent<ECS::ScriptComponent>(sc);
		}

		m_Project->AddEntity(entity);
	}

}