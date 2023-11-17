#pragma once

// Note(Jorben): Since C# doesn't support direct import/export of templated functions, we have to recreate these functions for every templated type as a standalone function.

#include "Crystal/ECS/Component.hpp"

#include <string>

namespace Crystal::Wrapper
{

	class Component
	{
	public:
		// TagComponent
		static void TagComponent_SetTag(uint64_t uuid, Coral::NativeString str);
		static Coral::NativeString TagComponent_GetTag(uint64_t uuid);

		// TransformComponent // TODO(Jorben): Use Vec3's?
		static void TransformComponent_SetPositionX(uint64_t uuid, float value);
		static void TransformComponent_SetPositionY(uint64_t uuid, float value);
		static void TransformComponent_SetPositionZ(uint64_t uuid, float value);
		static void TransformComponent_SetSizeX(uint64_t uuid, float value);
		static void TransformComponent_SetSizeY(uint64_t uuid, float value);
		static void TransformComponent_SetSizeZ(uint64_t uuid, float value);
		static void TransformComponent_SetRotation(uint64_t uuid, float value);

		static float TransformComponent_GetPositionX(uint64_t uuid);
		static float TransformComponent_GetPositionY(uint64_t uuid);
		static float TransformComponent_GetPositionZ(uint64_t uuid);
		static float TransformComponent_GetSizeX(uint64_t uuid);
		static float TransformComponent_GetSizeY(uint64_t uuid);
		static float TransformComponent_GetSizeZ(uint64_t uuid);
		static float TransformComponent_GetRotation(uint64_t uuid);

		// ScriptComponent
		static void ScriptComponent_AddValueField_Byte(uint64_t uuid, uint8_t byte);
		static void ScriptComponent_AddValueField_SByte(uint64_t uuid, int8_t sbyte);
		static void ScriptComponent_AddValueField_Short(uint64_t uuid, int16_t shortVar);
		static void ScriptComponent_AddValueField_UShort(uint64_t uuid, uint16_t ushortVar);
		static void ScriptComponent_AddValueField_Int(uint64_t uuid, int32_t intVar);
		static void ScriptComponent_AddValueField_UInt(uint64_t uuid, uint32_t uintVar);
		static void ScriptComponent_AddValueField_Long(uint64_t uuid, int64_t longVar);
		static void ScriptComponent_AddValueField_ULong(uint64_t uuid, uint64_t ulongVar);
		static void ScriptComponent_AddValueField_Float(uint64_t uuid, float floatVar);
		static void ScriptComponent_AddValueField_Double(uint64_t uuid, double doubleVar);
		static void ScriptComponent_AddValueField_Char(uint64_t uuid, char charVar);
		static void ScriptComponent_AddValueField_Bool(uint64_t uuid, bool boolVar);
		static void ScriptComponent_AddValueField_String(uint64_t uuid, std::string stringVar);
	};

}