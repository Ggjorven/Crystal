#include "crpch.h"
#include "EntityWrapper.hpp"

#include "Crystal/Data/Project/Project.hpp"
#include "Crystal/ECS/Storage.hpp"

namespace Crystal::Wrapper
{

	void Entity::AddTagComponent(uint64_t uuid, Coral::NativeString tag)
	{
		auto& tagComponent = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TagComponent>(uuid);
		tagComponent.Tag = std::string(tag);
	}

	void Entity::AddTransformComponent(uint64_t uuid, Vec3<float> position, Vec3<float> size, float rotation)
	{
		auto& transformComponent = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
		transformComponent.Position = position;
		transformComponent.Size = size;
		transformComponent.Rotation = rotation;
	}

	bool Entity::HasComponent_TagComponent(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TagComponent>(uuid);
	}

	bool Entity::HasComponent_TransformComponent(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid);
	}

	bool Entity::HasComponent_Renderer2DComponent(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid);
	}

	bool Entity::HasComponent_ScriptComponent(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::ScriptComponent>(uuid);
	}

	bool Entity::HasComponent_ColliderComponent(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::ColliderComponent>(uuid);
	}

}