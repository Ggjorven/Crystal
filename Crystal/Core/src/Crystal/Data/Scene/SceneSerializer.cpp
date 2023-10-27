#include "crpch.h"
#include "SceneSerializer.hpp"

#include <glm/glm.hpp>

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
		YAML::Node data;

		data["Entity"]["Size"][0] = 17.0f;
		data["Entity"]["Size"][1] = 15.0f;
		data["Entity"]["Position"][0] = 10.0f;
		data["Entity"]["Position"][1] = 2.75f;

		std::ofstream file(path);

		if (file.good())
		{
			file << data;
			file.close();
		}
		else
			CR_CORE_ERROR("Failed to open file {0}", path.string());
	}

	void SceneSerializer::Deserialize(std::filesystem::path path)
	{
		YAML::Node data = YAML::LoadFile(path.string());

		//CR_CORE_TRACE("Info: [Test] = '{0}', [Abc] = '{1}'", data["Test"].as<int>(), data["Abc"].as<std::string>());
		CR_CORE_TRACE("Entity Info:");
		CR_CORE_TRACE("	[Size] = X: {0}, Y: {1}", data["Entity"]["Size"][0].as<float>(), data["Entity"]["Size"][1].as<float>());
		CR_CORE_TRACE("	[Position] = X: {0}, Y: {1}", data["Entity"]["Position"][0].as<float>(), data["Entity"]["Position"][1].as<float>());
	}

}