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

		data << YAML::Key << "Scenes";
		data << YAML::Value << YAML::BeginSeq;

		for (auto& scenePath : m_Project->m_Scenes)
		{
			data << YAML::BeginMap; // Entity
			data << YAML::Key << "Scene";
			data << YAML::Value << scenePath.string();
		}

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
		int i = 0; // TEMP // REMOVE
		CR_CORE_TRACE("Loading project: {0}", path.string());
		
		YAML::Node data = YAML::LoadFile(path.string());

		//Set scene name
		if (data["Project"])
			m_Project->m_DebugName = data["Project"].as<std::string>();
		else
			CR_CORE_WARN("No \"Project:\" tab found in {0}\n\tNot critical, just no data loaded and starting as a blank project.", path.string());

		CR_CORE_TRACE("{0}", i++);

		auto scenes = data["Scenes"];
		if (scenes)
		{
			for (auto scene : scenes)
			{
				// TODO(Jorben): Add a way of saying a scene is 2D or 3D in YAML
				CR_CORE_TRACE("{0}", i++);
				
				CR_CORE_TRACE("Scene: {0}", scene["Scene"].as<std::string>());
				m_Project->m_Scenes.push_back(scene["Scene"].as<std::string>());
			}
			CR_CORE_TRACE("{0}", i++);
			if (m_Project->m_Scenes.size() > 0) m_Project->LoadScene2D(m_Project->m_Scenes[0]);
			else m_Project->m_ActiveScene = CreateRef<Scene2D>(); // TODO(Jorben): This doesn't make the program work
			CR_CORE_TRACE("{0}", i++);
		}
		CR_CORE_TRACE("Finished scenes");
		
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