#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Data/Project/Project.hpp"

#include <filesystem>

#include <yaml-cpp/yaml.h>

namespace Crystal
{

	class ProjectSerializer
	{
	public:
		ProjectSerializer(Ref<Project>& project);
		virtual ~ProjectSerializer();

		void Serialize(std::filesystem::path path);
		void Deserialize(std::filesystem::path path);

		ProjectSerializer& operator = (const ProjectSerializer& other);

	private:
		void SerializeEntity(YAML::Emitter& emitter, ECS::Entity& entity);
		void DeserializeEntity(YAML::detail::iterator_value& node);

	private:
		Ref<Project>& m_Project;
	};

}