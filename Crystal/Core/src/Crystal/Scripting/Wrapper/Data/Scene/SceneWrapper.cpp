#include "crpch.h"
#include "SceneWrapper.hpp"

#include "Crystal/Data/Project/Project.hpp"

namespace Crystal::Wrapper
{

	std::unordered_map<SceneID, std::unordered_map<std::string, CR_UUID>> Scene::s_UUIDCache;

	uint64_t Scene::GetUUIDByTag(Coral::NativeString tag)
	{
		//Check if cached
		if (s_UUIDCache[Project::GetCurrentProject()->GetCurrentScene()->GetSceneID()].find(std::string(tag)) != s_UUIDCache[Project::GetCurrentProject()->GetCurrentScene()->GetSceneID()].end())
		{
			return s_UUIDCache[Project::GetCurrentProject()->GetCurrentScene()->GetSceneID()][std::string(tag)];
		}

		ECS::Storage& storage = Project::GetCurrentProject()->GetCurrentScene()->GetStorage();
		
		// Check if it exists
		for (auto& tagMapItem : storage.GetComponentsMap<ECS::TagComponent>())
		{
			auto& tc = storage.GetComponent<ECS::TagComponent>(tagMapItem.first);

			if (tc.Tag == std::string(tag))
			{
				// Cache it
				s_UUIDCache[Project::GetCurrentProject()->GetCurrentScene()->GetSceneID()][std::string(tag)] = tagMapItem.first;

				return tagMapItem.first;
			}
		}

		return 0u;
	}

	void Scene::SetSceneByName(Coral::NativeString name)
	{
		Project::GetCurrentProject()->SetSceneBasedOnName(std::string(name));
	}

}