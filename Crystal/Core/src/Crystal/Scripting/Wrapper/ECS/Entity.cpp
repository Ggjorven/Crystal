#include "crpch.h"
#include "Entity.hpp"

#include "Crystal/Data/Project/Project.hpp"
#include "Crystal/ECS/Storage.hpp"

namespace Crystal::Wrapper
{

	void Entity::AddTagComponent(uint64_t uuid, Coral::NativeString tag)
	{
		Ref<ECS::TagComponent> tagComponent = CreateRef<ECS::TagComponent>();
		tagComponent->Tag = std::string(tag);

		Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TagComponent>(uuid, tagComponent);
	}

	void Entity::AddTransformComponent(uint64_t uuid, Vec3<float> position, Vec3<float> size, float rotation)
	{
		Ref<ECS::TransformComponent> transformComponent = CreateRef<ECS::TransformComponent>();
		transformComponent->Position = position;
		transformComponent->Size = size;
		transformComponent->Rotation = rotation;

		Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, transformComponent);
	}

}