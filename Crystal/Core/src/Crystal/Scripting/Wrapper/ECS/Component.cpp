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

	void Component::TagComponent_SetTag(uint64_t uuid, Coral::NativeString str)
	{
		ECS::TagComponent* tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TagComponent>(uuid);

		if (tc)
		{
			tc->Tag = std::string(str);
		}
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

}