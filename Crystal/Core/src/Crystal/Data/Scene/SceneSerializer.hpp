#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Data/Scene/Scene.hpp"

#include <filesystem>

#include <yaml-cpp/yaml.h>

namespace Crystal
{

	class SceneSerializer
	{
	public:
		SceneSerializer(Ref<Scene>& scene);
		virtual ~SceneSerializer();

		void Serialize(std::filesystem::path path);
		void Deserialize(std::filesystem::path path);

	private:
		void SerializeEntity(YAML::Emitter& emitter, ECS::Entity& entity);
		void DeserializeEntity(YAML::detail::iterator_value& node);

	private:
		Ref<Scene>& m_Scene;
	};

}