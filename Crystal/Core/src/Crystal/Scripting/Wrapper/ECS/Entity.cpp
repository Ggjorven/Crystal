#include "crpch.h"
#include "Entity.hpp"

#include "Crystal/Data/Project/Project.hpp"
#include "Crystal/ECS/Storage.hpp"

namespace Crystal::Wrapper
{

	void Entity::AddTagComponent(uint64_t uuid, Coral::NativeString tag)
	{
		auto& tagComponent = Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TagComponent>(uuid);
		tagComponent.Tag = std::string(tag);
	}

	void Entity::AddTransformComponent(uint64_t uuid, Vec3<float> position, Vec3<float> size, float rotation)
	{
		auto& transformComponent = Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
		transformComponent.Position = position;
		transformComponent.Size = size;
		transformComponent.Rotation = rotation;
	}

}