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
		Ref<ECS::TagComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TagComponent>(uuid);

		if (tc)
			tc->Tag = std::string(str);
		else
		{
			Ref<ECS::TagComponent> newTc = CreateRef<ECS::TagComponent>();
			newTc->Tag = std::string(str);

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
		Ref<ECS::TransformComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Position.X = value;
		else
		{
			Ref<ECS::TransformComponent> newTc = CreateRef<ECS::TransformComponent>();
			newTc->Position.X = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetPositionY(uint64_t uuid, float value)
	{
		Ref<ECS::TransformComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Position.Y = value;
		else
		{
			Ref<ECS::TransformComponent> newTc = CreateRef<ECS::TransformComponent>();
			newTc->Position.Y = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetPositionZ(uint64_t uuid, float value)
	{
		Ref<ECS::TransformComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Position.Z = value;
		else
		{
			Ref<ECS::TransformComponent> newTc = CreateRef<ECS::TransformComponent>();
			newTc->Position.Z = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetSizeX(uint64_t uuid, float value)
	{
		Ref<ECS::TransformComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Size.X = value;
		else
		{
			Ref<ECS::TransformComponent> newTc = CreateRef<ECS::TransformComponent>();
			newTc->Size.X = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetSizeY(uint64_t uuid, float value)
	{
		Ref<ECS::TransformComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Size.Y = value;
		else
		{
			Ref<ECS::TransformComponent> newTc = CreateRef<ECS::TransformComponent>();
			newTc->Size.Y = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetSizeZ(uint64_t uuid, float value)
	{
		Ref<ECS::TransformComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Size.Z = value;
		else
		{
			Ref<ECS::TransformComponent> newTc = CreateRef<ECS::TransformComponent>();
			newTc->Size.Z = value;

			Project::GetCurrentProject()->GetStorage().AddComponent<ECS::TransformComponent>(uuid, newTc);
		}
	}

	void Component::TransformComponent_SetRotation(uint64_t uuid, float value)
	{
		Ref<ECS::TransformComponent> tc = Project::GetCurrentProject()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);

		if (tc)
			tc->Rotation = value;
		else
		{
			Ref<ECS::TransformComponent> newTc = CreateRef<ECS::TransformComponent>();
			newTc->Rotation = value;

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

	/*
		ScriptComponent
	*/
	void Component::ScriptComponent_AddValueField_Byte(uint64_t uuid, Coral::NativeString name, uint8_t byte)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_SByte(uint64_t uuid, Coral::NativeString name, int8_t sbyte)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_Short(uint64_t uuid, Coral::NativeString name, int16_t shortVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_UShort(uint64_t uuid, Coral::NativeString name, uint16_t ushortVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_Int(uint64_t uuid, Coral::NativeString name, int32_t intVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_UInt(uint64_t uuid, Coral::NativeString name, uint32_t uintVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_Long(uint64_t uuid, Coral::NativeString name, int64_t longVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_ULong(uint64_t uuid, Coral::NativeString name, uint64_t ulongVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_Float(uint64_t uuid, Coral::NativeString name, float floatVar)
	{
		CR_CORE_TRACE("{0} {1}, {2}, {3}", __FUNCTION__, uuid, std::string(name), floatVar);
	}

	void Component::ScriptComponent_AddValueField_Double(uint64_t uuid, Coral::NativeString name, double doubleVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_Char(uint64_t uuid, Coral::NativeString name, char charVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_Bool(uint64_t uuid, Coral::NativeString name, bool boolVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}

	void Component::ScriptComponent_AddValueField_String(uint64_t uuid, Coral::NativeString name, Coral::NativeString stringVar)
	{
		CR_CORE_TRACE("{0}", __FUNCTION__);
	}


}