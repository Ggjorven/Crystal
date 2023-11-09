#include "crpch.h"
#include "Entity.hpp"

#include "Crystal/Data/Project/Project.hpp"
#include "Crystal/ECS/Storage.hpp"

namespace Crystal::Wrapper
{

	void Entity::AddTagComponent(uint64_t uuid, Coral::NativeString tag)
	{
		ECS::TagComponent tagComponent;
		tagComponent.Tag = std::string(tag);

		Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TagComponent>(uuid, tagComponent);
	}

}