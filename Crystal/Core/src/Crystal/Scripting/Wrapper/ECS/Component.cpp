#include "crpch.h"
#include "Component.hpp"

#include "Crystal/Data/Project/Project.hpp"
#include "Crystal/ECS/Storage.hpp"

namespace Crystal::Wrapper
{

	/*
		TagComponent
	*/
	void Component::TagComponent_SetTag(uint64_t uuid, Coral::NativeString str)
	{
		ECS::TagComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TagComponent>(uuid);

		if (tc)
			tc->Tag = std::string(str);
		else
		{
			ECS::TagComponent newTc = ECS::TagComponent();
			newTc.Tag = std::string(str);

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TagComponent>(uuid, newTc);
		}
	}

	Coral::NativeString Component::TagComponent_GetTag(uint64_t uuid)
	{
		return Coral::NativeString(Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TagComponent>(uuid)->Tag);
	}

	/*
		TransformComponent
	*/
	void Component::TransformComponent_SetPositionX(uint64_t uuid, float value)
	{
		ECS::TransformComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Position.X = value;
		else
		{
			ECS::TransformComponent newTc = ECS::TransformComponent();
			newTc.Position.X = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetPositionY(uint64_t uuid, float value)
	{
		ECS::TransformComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Position.Y = value;
		else
		{
			ECS::TransformComponent newTc = ECS::TransformComponent();
			newTc.Position.Y = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetPositionZ(uint64_t uuid, float value)
	{
		ECS::TransformComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Position.Z = value;
		else
		{
			ECS::TransformComponent newTc = ECS::TransformComponent();
			newTc.Position.Z = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetSizeX(uint64_t uuid, float value)
	{
		ECS::TransformComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Size.X = value;
		else
		{
			ECS::TransformComponent newTc = ECS::TransformComponent();
			newTc.Size.X = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetSizeY(uint64_t uuid, float value)
	{
		ECS::TransformComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Size.Y = value;
		else
		{
			ECS::TransformComponent newTc = ECS::TransformComponent();
			newTc.Size.Y = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetSizeZ(uint64_t uuid, float value)
	{
		ECS::TransformComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Size.Z = value;
		else
		{
			ECS::TransformComponent newTc = ECS::TransformComponent();
			newTc.Size.Z = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetRotation(uint64_t uuid, float value)
	{
		ECS::TransformComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Rotation = value;
		else
		{
			ECS::TransformComponent newTc = ECS::TransformComponent();
			newTc.Rotation = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	float Component::TransformComponent_GetPositionX(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid)->Position.X;
	}

	float Component::TransformComponent_GetPositionY(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid)->Position.Y;
	}

	float Component::TransformComponent_GetPositionZ(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid)->Position.Z;
	}

	float Component::TransformComponent_GetSizeX(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid)->Size.X;
	}

	float Component::TransformComponent_GetSizeY(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid)->Size.Y;
	}

	float Component::TransformComponent_GetSizeZ(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid)->Size.Z;
	}

	float Component::TransformComponent_GetRotation(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid)->Rotation;
	}

}