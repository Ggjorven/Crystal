#include "crpch.h"
#include "SceneSerializer.hpp"

#include "Crystal/Data/Project/Project.hpp"

#include "Crystal/Utils/YamlUtils.hpp"

#include "Crystal/Renderer/RendererCommand.hpp"

namespace Crystal
{

	SceneSerializer::SceneSerializer(Scene* scene)
		: m_PureScene(scene)
	{
	}

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

		Scene* scene = nullptr;
		if (m_Scene) scene = m_Scene.get();
		else scene = m_PureScene;

		data << YAML::BeginMap;
		data << YAML::Key << "Scene";
		data << YAML::Value << scene->GetName();

		std::set<std::string> set = { };
		for (auto& assembly : scene->GetStorage().s_AssemblyPaths)
			set.insert(assembly.string());

		std::vector<std::string> assemblies = { };
		for (auto& item : set)
			assemblies.emplace_back(item);
		
		data << YAML::Key << "Assemblies";
		data << YAML::Value << assemblies;

		data << YAML::Key << "ClearColour";
		data << YAML::Value << glm::vec4(scene->m_ClearColour);

		data << YAML::Key << "Entities";
		data << YAML::Value << YAML::BeginSeq;

		for (Ref<ECS::Entity>& entity : scene->m_Entities)
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
		CR_CORE_TRACE("Loading scene: {0}", path.string());

		YAML::Node data;

		Scene* scene = nullptr;
		if (m_Scene) scene = m_Scene.get();
		else scene = m_PureScene;

		try
		{
			data = YAML::LoadFile(path.string());
		}
		catch (YAML::BadFile e)
		{
			CR_CORE_ERROR("Failed to load {0}\n\t{1}", path.string(), e.what());
			//return;
		}

		//Set scene name
		//scene->m_Properties.Path = path;
		if (data["Scene"])
		{
			scene->m_DebugName = data["Scene"].as<std::string>();
			//scene->m_Properties.Name = data["Scene"].as<std::string>();
		}
		else
			CR_CORE_WARN("No \"Scene:\" tab found in {0}\n\tNot critical, just no data loaded and starting as a blank scene.", path.string());

		if (data["Assemblies"])
		{
			std::vector<std::string> assemblies = data["Assemblies"].as<std::vector<std::string>>();
			for (auto& assembly : assemblies)
			{
				std::filesystem::path projDir = Project::GetCurrentProject()->GetProjectDir();
				std::filesystem::path scriptDir = Project::GetCurrentProject()->GetScriptsDir();
				scene->GetStorage().AddPath(assembly);
				scene->GetStorage().LoadAssembly(projDir / scriptDir / assembly);
			}
		}

		if (data["ClearColour"])
		{
			scene->m_ClearColour = data["ClearColour"].as<glm::vec4>();
			RendererCommand::SetClearColour(scene->m_ClearColour);
		}
		else
		{
			scene->m_ClearColour = { 0.0f, 0.0f, 0.0f, 1.0f };
			RendererCommand::SetClearColour(scene->m_ClearColour);
		}

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
				DeserializeEntity(entity);
		}
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
				emitter << YAML::Key << "Texture" << r2d.Texture->GetProjectRelativePath();
			emitter << YAML::Key << "Colour" << r2d.Colour;
			emitter << YAML::Key << "UseTexture" << r2d.UseTexture;
			emitter << YAML::Key << "UseColour" << r2d.UseColour;

			emitter << YAML::EndMap; // Renderer2DComponent
		}

		if (entity->HasComponent<ECS::Renderer3DComponent>())
		{
			auto& r2d = entity->GetComponent<ECS::Renderer3DComponent>();
			emitter << YAML::Key << "Renderer3DComponent";
			emitter << YAML::BeginMap; // Renderer3DComponent

			emitter << YAML::Key << "Enable" << r2d.Enable;
			if (r2d.Texture)
				emitter << YAML::Key << "Texture" << r2d.Texture->GetProjectRelativePath();
			emitter << YAML::Key << "Colour" << r2d.Colour;
			emitter << YAML::Key << "UseTexture" << r2d.UseTexture;
			emitter << YAML::Key << "UseColour" << r2d.UseColour;

			emitter << YAML::EndMap; // Renderer3DComponent
		}

		if (entity->HasComponent<ECS::ColliderComponent>())
		{
			auto& cc = entity->GetComponent<ECS::ColliderComponent>();
			emitter << YAML::Key << "ColliderComponent";
			emitter << YAML::BeginMap; // ColliderComponent

			if (cc.AABB)
			{
				emitter << YAML::Key << "AABB";
				emitter << YAML::BeginMap; //AABB

				emitter << YAML::Key << "Position-Link" << cc.AABB->LinkedPosition();
				emitter << YAML::Key << "Size-Link" << cc.AABB->LinkedSize();
				emitter << YAML::Key << "Position" << glm::vec3(cc.AABB->GetPosition());
				emitter << YAML::Key << "Size" << glm::vec3(cc.AABB->GetSize());

				emitter << YAML::EndMap; //AABB
			}

			emitter << YAML::EndMap; // ColliderComponent
		}

		if (entity->HasComponent<ECS::ScriptComponent>())
		{
			auto& sc = entity->GetComponent<ECS::ScriptComponent>();
			emitter << YAML::Key << "ScriptComponent";
			emitter << YAML::BeginMap; // ScriptComponent

			emitter << YAML::Key << "Class" << sc.Script->GetClass();

			emitter << YAML::EndMap; // ScriptComponent
		}

		if (entity->HasComponent<ECS::CameraComponent2D>())
		{
			auto& cc = entity->GetComponent<ECS::CameraComponent2D>();
			emitter << YAML::Key << "CameraComponent2D";
			emitter << YAML::BeginMap; // CameraComponent2D

			emitter << YAML::Key << "Position" << glm::vec2(cc.Position);
			emitter << YAML::Key << "Size" << cc.Size;
			emitter << YAML::Key << "Zoom" << cc.Zoom;
			emitter << YAML::Key << "Rotation" << cc.Rotation;

			emitter << YAML::Key << "Primary" << cc.Primary;

			emitter << YAML::EndMap; // CameraComponent2D
		}

		if (entity->HasComponent<ECS::CameraComponent3D>())
		{
			auto& cc = entity->GetComponent<ECS::CameraComponent3D>();
			emitter << YAML::Key << "CameraComponent3D";
			emitter << YAML::BeginMap; // CameraComponent3D

			emitter << YAML::Key << "Position" << glm::vec3(cc.Position);
			emitter << YAML::Key << "Size" << cc.Size;
			emitter << YAML::Key << "Zoom" << cc.Zoom;
			emitter << YAML::Key << "Rotation" << cc.Rotation;

			emitter << YAML::Key << "Primary" << cc.Primary;

			emitter << YAML::Key << "FOV" << cc.FOV;

			emitter << YAML::EndMap; // CameraComponent3D
		}

		emitter << YAML::EndMap; //Entity
	}

	void SceneSerializer::DeserializeEntity(YAML::detail::iterator_value& node)
	{
		uint64_t uuid = node["Entity"].as<uint64_t>();

		Scene* scene = nullptr;
		if (m_Scene) scene = m_Scene.get();
		else scene = m_PureScene;

		//Creation of the Entity
		Ref<ECS::Entity> entity = ECS::Entity::Create(scene->m_Storage);
		entity->SetUUID(uuid);
		scene->AddEntity(entity);

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
			if (renderer2DComponent["Texture"] && !renderer2DComponent["Texture"].as<std::string>().empty())
			{
				std::filesystem::path projDir = Project::GetCurrentProject()->GetProjectDir();
				std::filesystem::path assetDir = Project::GetCurrentProject()->GetAssetDir();

				r2d.Texture = Texture2D::Create((projDir / assetDir / std::filesystem::path(renderer2DComponent["Texture"].as<std::string>())).string());
			}
			else
				r2d.Texture = nullptr;

			r2d.Colour = renderer2DComponent["Colour"].as<glm::vec4>();
			r2d.UseTexture = renderer2DComponent["UseTexture"].as<bool>();
			r2d.UseColour = renderer2DComponent["UseColour"].as<bool>();
		}

		//Renderer3DComponent
		auto renderer3DComponent = node["Renderer3DComponent"];
		if (renderer3DComponent)
		{
			ECS::Renderer3DComponent& r3d = entity->AddComponent<ECS::Renderer3DComponent>();

			r3d.Enable = renderer3DComponent["Enable"].as<bool>();
			if (renderer3DComponent["Texture"] && !renderer3DComponent["Texture"].as<std::string>().empty())
			{
				std::filesystem::path projDir = Project::GetCurrentProject()->GetProjectDir();
				std::filesystem::path assetDir = Project::GetCurrentProject()->GetAssetDir();

				r3d.Texture = Texture2D::Create((projDir / assetDir / std::filesystem::path(renderer3DComponent["Texture"].as<std::string>())).string());
			}
			else
				r3d.Texture = nullptr;

			r3d.Colour = renderer3DComponent["Colour"].as<glm::vec4>();
			r3d.UseTexture = renderer3DComponent["UseTexture"].as<bool>();
			r3d.UseColour = renderer3DComponent["UseColour"].as<bool>();
		}

		//ColliderComponent
		auto colliderComponent = node["ColliderComponent"];
		if (colliderComponent)
		{
			ECS::ColliderComponent& cc = entity->AddComponent<ECS::ColliderComponent>();

			auto AABB = colliderComponent["AABB"];
			if (AABB)
			{
				cc.AABB = CreateRef<AABBCollider>();

				cc.AABB->SetPostionLinked(AABB["Position-Link"].as<bool>());
				cc.AABB->SetSizeLinked(AABB["Size-Link"].as<bool>());
				cc.AABB->SetPosition(AABB["Position"].as<glm::vec3>());
				cc.AABB->SetSize(AABB["Size"].as<glm::vec3>());
			}
		}

		//ScriptComponent
		auto scriptComponent = node["ScriptComponent"];
		if (scriptComponent)
		{
			ECS::ScriptComponent& sc = entity->AddComponent<ECS::ScriptComponent>();

			sc.Script->SetUUID(entity->GetUUID());
			sc.Script->SetClass(scriptComponent["Class"].as<std::string>());
		}

		//CameraComponent2D
		auto cameraComponent2D = node["CameraComponent2D"];
		if (cameraComponent2D)
		{
			ECS::CameraComponent2D& cc = entity->AddComponent<ECS::CameraComponent2D>();

			cc.Position = cameraComponent2D["Position"].as<glm::vec2>();
			cc.Size = cameraComponent2D["Size"].as<glm::vec2>();
			cc.Zoom = cameraComponent2D["Zoom"].as<float>();
			cc.Rotation = cameraComponent2D["Rotation"].as<float>();

			cc.Primary = cameraComponent2D["Primary"].as<bool>();
		}

		//CameraComponent3D
		auto cameraComponent3D = node["CameraComponent3D"];
		if (cameraComponent3D)
		{
			ECS::CameraComponent3D& cc = entity->AddComponent<ECS::CameraComponent3D>();

			cc.Position = cameraComponent3D["Position"].as<glm::vec3>();
			cc.Size = cameraComponent3D["Size"].as<glm::vec2>();
			cc.Zoom = cameraComponent3D["Zoom"].as<float>();
			cc.Rotation = cameraComponent3D["Rotation"].as<float>();

			cc.FOV = cameraComponent3D["FOV"].as<float>();

			cc.Primary = cameraComponent3D["Primary"].as<bool>();
		}
	}

}