#include "crpch.h"
#include "Component.hpp"

#include "Crystal/Data/Project/Project.hpp"
#include "Crystal/ECS/Storage.hpp"

namespace Crystal::Wrapper
{

	//ECS::TransformComponent* Component::GetComponent_TransformComponent(CR_UUID uuid)
	//{
	//	return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
	//}

	void TagComponent_SetTag(uint64_t uuid, Coral::NativeString str)
	{
		Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TagComponent>(uuid)->Tag = std::string(str);
	}

	Coral::NativeString TagComponent_GetTag(uint64_t uuid)
	{
		return Coral::NativeString(Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TagComponent>(uuid)->Tag);
	}

}