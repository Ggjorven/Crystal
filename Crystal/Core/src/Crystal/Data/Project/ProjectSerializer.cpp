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

		// Dirs
		data << YAML::Key << "Directories";
		data << YAML::Value << YAML::BeginSeq;

		data << YAML::BeginMap;
		data << YAML::Key << "Assets";
		data << YAML::Value << m_Project->m_AssetDir.string();
		data << YAML::EndMap;

		data << YAML::BeginMap;
		data << YAML::Key << "Scenes";
		data << YAML::Value << m_Project->m_SceneDir.string();
		data << YAML::EndMap;

		data << YAML::BeginMap;
		data << YAML::Key << "Scripts";
		data << YAML::Value << m_Project->m_ScriptsDir.string();
		data << YAML::EndMap;


		data << YAML::EndSeq;

		data << YAML::Key << "Scenes";
		data << YAML::Value << YAML::BeginSeq;

		for (auto& sceneProperties : m_Project->m_Scenes)
		{
			data << YAML::BeginMap; // Scene
			data << YAML::Key << "Scene";
			data << YAML::BeginMap; // Scene

			data << YAML::Key << "Name";
			data << YAML::Value << sceneProperties.Name;
			
			data << YAML::Key << "Path";
			data << YAML::Value << sceneProperties.Path.string();

			std::string type;
			if (sceneProperties.SceneType == SceneProperties::Type::_2D) type = "2D";
			else if (sceneProperties.SceneType == SceneProperties::Type::_3D) type = "3D";

			data << YAML::Key << "Type";
			data << YAML::Value << type;

			data << YAML::EndMap; // Scene
			data << YAML::EndMap; // Scene
		}

		data << YAML::EndSeq << YAML::EndMap;

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

	void ProjectSerializer::Deserialize(std::filesystem::path path)
	{
		CR_CORE_TRACE("Loading project: {0}", path.string());
		
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(path.string());
		}
		catch (YAML::BadFile e)
		{
			CR_CORE_ERROR("Failed to load {0}", path.string());
			return;
		}

		m_Project->m_ProjectDir = path.parent_path();

		//Set scene name
		if (data["Project"])
			m_Project->m_DebugName = data["Project"].as<std::string>();
		else
		{
			CR_CORE_WARN("No \"Project:\" tab found in {0}\n\tNot critical, just no data loaded and starting as a blank project.", path.string());
		}

		//Directories
		auto directories = data["Directories"];
		if (directories)
		{
			// TODO(Jorben): Add a better way to go though Directories
			for (auto dir : directories)
			{
				auto assets = dir["Assets"];
				if (assets) m_Project->m_AssetDir = std::filesystem::path(assets.as<std::string>());

				auto scenes = dir["Scenes"];
				if (scenes) m_Project->m_SceneDir = std::filesystem::path(scenes.as<std::string>());

				auto scripts = dir["Scripts"];
				if (scripts) m_Project->m_ScriptsDir = std::filesystem::path(scripts.as<std::string>());
			}
		}
		else
		{
			m_Project->m_AssetDir = std::filesystem::path("Assets");
			m_Project->m_SceneDir = std::filesystem::path("Scenes");
			m_Project->m_ScriptsDir = std::filesystem::path("Scripts");
		}

		//Scenes
		auto scenes = data["Scenes"];
		if (scenes)
		{
			for (auto scene : scenes)
			{
				// TODO(Jorben): Add a way of saying a scene is 2D or 3D in YAML
				SceneProperties properties;

				auto sceneData = scene["Scene"];
				if (sceneData)
				{
					properties.Name = sceneData["Name"].as<std::string>();
					properties.Path = sceneData["Path"].as<std::string>();

					SceneProperties::Type type = SceneProperties::Type::_2D;
					if (sceneData["Type"].as<std::string>() == "3D") type = SceneProperties::Type::_3D;
					properties.SceneType = type;
				}

				m_Project->m_Scenes.emplace_back(properties);
			}
		}
		// TODO(Jorben): Add a way of saying a scene is 2D or 3D in YAML
		// TODO(Jorben): Use the startproject defined in the .crproj file as the AddScene scene.
		if (m_Project->m_Scenes.size() > 0)
		{
			m_Project->SetScene(m_Project->m_Scenes[0]);
		}
		else
		{
			std::ofstream file(m_Project->GetProjectDir() / m_Project->GetSceneDir() / std::filesystem::path("New.crscene"));
			file << " " << std::endl;
			file.close();

			SceneProperties properties;
			properties.Path = std::filesystem::path("New.crscene");

			m_Project->m_Scenes.emplace_back(properties);

			m_Project->SetScene(m_Project->m_Scenes[0]);
		}
		
		std::stringstream ss;
		ss << data;
	}

	ProjectSerializer& ProjectSerializer::operator=(const ProjectSerializer& other)
	{
		if (this != &other)
			m_Project = other.m_Project;

		return *this;
	}
}