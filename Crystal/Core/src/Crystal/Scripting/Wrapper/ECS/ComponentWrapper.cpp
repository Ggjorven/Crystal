#include "crpch.h"
#include "ComponentWrapper.hpp"

#include "Crystal/Data/Project/Project.hpp"
#include "Crystal/ECS/Storage.hpp"

namespace Crystal::Wrapper
{

	/*
		TagComponent
	*/
	void Component::TagComponent_SetTag(uint64_t uuid, Coral::NativeString str)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TagComponent>(uuid))
		{
			ECS::TagComponent& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TagComponent>(uuid);
			tc.Tag = std::string(str);
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TagComponent>(uuid);
			newTc.Tag = std::string(str);
		}
	}

	Coral::NativeString Component::TagComponent_GetTag(uint64_t uuid)
	{
		return Coral::NativeString(Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TagComponent>(uuid).Tag);
	}

	/*
		TransformComponent
	*/
	void Component::TransformComponent_SetPositionX(uint64_t uuid, float value)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
			tc.Position.X = value;
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
			newTc.Position.X = value;
		}
	}

	void Component::TransformComponent_SetPositionY(uint64_t uuid, float value)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
			tc.Position.Y = value;
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
			newTc.Position.Y = value;
		}
	}

	void Component::TransformComponent_SetPositionZ(uint64_t uuid, float value)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
			tc.Position.Z = value;
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
			newTc.Position.Z = value;
		}
	}

	void Component::TransformComponent_SetSizeX(uint64_t uuid, float value)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
			tc.Size.X = value;
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
			newTc.Size.X = value;
		}
	}

	void Component::TransformComponent_SetSizeY(uint64_t uuid, float value)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
			tc.Size.Y = value;
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
			newTc.Size.Y = value;
		}
	}

	void Component::TransformComponent_SetSizeZ(uint64_t uuid, float value)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
			tc.Size.Z = value;
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
			newTc.Size.Z = value;
		}
	}

	void Component::TransformComponent_SetRotation(uint64_t uuid, float value)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::TransformComponent>(uuid))
		{
			auto& tc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid);
			tc.Rotation = value;
		}
		else
		{
			auto& newTc = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::TransformComponent>(uuid);
			newTc.Rotation = value;
		}
	}

	float Component::TransformComponent_GetPositionX(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid).Position.X;
	}

	float Component::TransformComponent_GetPositionY(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid).Position.Y;
	}

	float Component::TransformComponent_GetPositionZ(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid).Position.Z;
	}

	float Component::TransformComponent_GetSizeX(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid).Size.X;
	}

	float Component::TransformComponent_GetSizeY(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid).Size.Y;
	}

	float Component::TransformComponent_GetSizeZ(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid).Size.Z;
	}

	float Component::TransformComponent_GetRotation(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::TransformComponent>(uuid).Rotation;
	}

	/*
		ScriptComponent
	*/
	void Component::ScriptComponent_AddValueField_Byte(uint64_t uuid, Coral::NativeString name, uint8_t byte)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<uint8_t>(std::string(name), byte);
	}

	void Component::ScriptComponent_AddValueField_SByte(uint64_t uuid, Coral::NativeString name, int8_t sbyte)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<int8_t>(std::string(name), sbyte);
	}

	void Component::ScriptComponent_AddValueField_Short(uint64_t uuid, Coral::NativeString name, int16_t shortVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<int16_t>(std::string(name), shortVar);
	}

	void Component::ScriptComponent_AddValueField_UShort(uint64_t uuid, Coral::NativeString name, uint16_t ushortVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<uint16_t>(std::string(name), ushortVar);
	}

	void Component::ScriptComponent_AddValueField_Int(uint64_t uuid, Coral::NativeString name, int32_t intVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<int32_t>(std::string(name), intVar);
	}

	void Component::ScriptComponent_AddValueField_UInt(uint64_t uuid, Coral::NativeString name, uint32_t uintVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<uint32_t>(std::string(name), uintVar);
	}

	void Component::ScriptComponent_AddValueField_Long(uint64_t uuid, Coral::NativeString name, int64_t longVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<int64_t>(std::string(name), longVar);
	}

	void Component::ScriptComponent_AddValueField_ULong(uint64_t uuid, Coral::NativeString name, uint64_t ulongVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<uint64_t>(std::string(name), ulongVar);
	}

	void Component::ScriptComponent_AddValueField_Float(uint64_t uuid, Coral::NativeString name, float floatVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<float>(std::string(name), floatVar);
	}

	void Component::ScriptComponent_AddValueField_Double(uint64_t uuid, Coral::NativeString name, double doubleVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<double>(std::string(name), doubleVar);
	}

	void Component::ScriptComponent_AddValueField_Char(uint64_t uuid, Coral::NativeString name, char charVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<char>(std::string(name), charVar);
	}

	void Component::ScriptComponent_AddValueField_Bool(uint64_t uuid, Coral::NativeString name, bool boolVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<bool>(std::string(name), boolVar);
	}

	void Component::ScriptComponent_AddValueField_String(uint64_t uuid, Coral::NativeString name, Coral::NativeString stringVar)
	{
		Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::ScriptComponent>(uuid).Script->AddValueField<std::string>(std::string(name), std::string(stringVar));
	}


}
