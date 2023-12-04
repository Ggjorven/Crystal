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
		Renderer2DComponent
	*/
	void Component::Renderer2DComponent_SetUseColour(uint64_t uuid, bool enabled)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid))
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid);
			r2d.UseColour = enabled;
		}
		else
		{
			auto& newR2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::Renderer2DComponent>(uuid);
			newR2d.UseColour = enabled;
		}
	}

	void Component::Renderer2DComponent_SetUseTexture(uint64_t uuid, bool enabled)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid))
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid);
			r2d.UseTexture = enabled;
		}
		else
		{
			auto& newR2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::Renderer2DComponent>(uuid);
			newR2d.UseTexture = enabled;
		}
	}

	void Component::Renderer2DComponent_SetColourR(uint64_t uuid, float colR)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid))
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid);
			r2d.Colour.R = colR;
		}
		else
		{
			auto& newR2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::Renderer2DComponent>(uuid);
			newR2d.Colour.R = colR;
		}
	}

	void Component::Renderer2DComponent_SetColourG(uint64_t uuid, float colG)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid))
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid);
			r2d.Colour.G = colG;
		}
		else
		{
			auto& newR2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::Renderer2DComponent>(uuid);
			newR2d.Colour.G = colG;
		}
	}

	void Component::Renderer2DComponent_SetColourB(uint64_t uuid, float colB)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid))
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid);
			r2d.Colour.B = colB;
		}
		else
		{
			auto& newR2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::Renderer2DComponent>(uuid);
			newR2d.Colour.B = colB;
		}
	}

	void Component::Renderer2DComponent_SetColourA(uint64_t uuid, float colA)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid))
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid);
			r2d.Colour.A = colA;
		}
		else
		{
			auto& newR2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::Renderer2DComponent>(uuid);
			newR2d.Colour.A = colA;
		}
	}

	void Component::Renderer2DComponent_SetTexturePath(uint64_t uuid, Coral::NativeString path)
	{
		if (Project::GetCurrentProject()->GetCurrentScene()->GetStorage().HasComponent<ECS::Renderer2DComponent>(uuid))
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid);
			std::filesystem::path relPath = Project::GetCurrentProject()->GetProjectDir() / Project::GetCurrentProject()->GetAssetDir() / std::filesystem::path(std::string(path));
			r2d.Texture = Texture2D::Create(relPath.string());
		}
		else
		{
			auto& r2d = Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddComponent<ECS::Renderer2DComponent>(uuid);
			std::filesystem::path relPath = Project::GetCurrentProject()->GetProjectDir() / Project::GetCurrentProject()->GetAssetDir() / std::filesystem::path(std::string(path));
			r2d.Texture = Texture2D::Create(relPath.string());
		}
	}

	bool Component::Renderer2DComponent_GetUseColour(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid).UseColour;
	}

	bool Component::Renderer2DComponent_GetUseTexture(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid).UseTexture;
	}

	Coral::NativeString Component::Renderer2DComponent_GetTexturePath(uint64_t uuid)
	{
		return Coral::NativeString(Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid).Texture->GetPath());
	}

	float Component::Renderer2DComponent_GetColourR(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid).Colour.R;
	}

	float Component::Renderer2DComponent_GetColourG(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid).Colour.G;
	}

	float Component::Renderer2DComponent_GetColourB(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid).Colour.B;
	}

	float Component::Renderer2DComponent_GetColourA(uint64_t uuid)
	{
		return Project::GetCurrentProject()->GetCurrentScene()->GetStorage().GetComponent<ECS::Renderer2DComponent>(uuid).Colour.A;
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
