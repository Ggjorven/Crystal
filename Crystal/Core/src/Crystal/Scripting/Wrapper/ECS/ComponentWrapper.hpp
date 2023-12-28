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

		// TransformComponent
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

		// Renderer2DComponent
		static void Renderer2DComponent_SetUseColour(uint64_t uuid, bool enabled);
		static void Renderer2DComponent_SetUseTexture(uint64_t uuid, bool enabled);

		static void Renderer2DComponent_SetColourR(uint64_t uuid, float colR);
		static void Renderer2DComponent_SetColourG(uint64_t uuid, float colG);
		static void Renderer2DComponent_SetColourB(uint64_t uuid, float colB);
		static void Renderer2DComponent_SetColourA(uint64_t uuid, float colA);

		static void Renderer2DComponent_SetTexturePath(uint64_t uuid, Coral::NativeString path);

		static bool Renderer2DComponent_GetUseColour(uint64_t uuid);
		static bool Renderer2DComponent_GetUseTexture(uint64_t uuid);

		static Coral::NativeString Renderer2DComponent_GetTexturePath(uint64_t uuid);

		static float Renderer2DComponent_GetColourR(uint64_t uuid);
		static float Renderer2DComponent_GetColourG(uint64_t uuid);
		static float Renderer2DComponent_GetColourB(uint64_t uuid);
		static float Renderer2DComponent_GetColourA(uint64_t uuid);

		// ScriptComponent
		static void ScriptComponent_AddValueField_Byte(uint64_t uuid, Coral::NativeString name, uint8_t byte);
		static void ScriptComponent_AddValueField_SByte(uint64_t uuid, Coral::NativeString name, int8_t sbyte);
		static void ScriptComponent_AddValueField_Short(uint64_t uuid, Coral::NativeString name, int16_t shortVar);
		static void ScriptComponent_AddValueField_UShort(uint64_t uuid, Coral::NativeString name, uint16_t ushortVar);
		static void ScriptComponent_AddValueField_Int(uint64_t uuid, Coral::NativeString name, int32_t intVar);
		static void ScriptComponent_AddValueField_UInt(uint64_t uuid, Coral::NativeString name, uint32_t uintVar);
		static void ScriptComponent_AddValueField_Long(uint64_t uuid, Coral::NativeString name, int64_t longVar);
		static void ScriptComponent_AddValueField_ULong(uint64_t uuid, Coral::NativeString name, uint64_t ulongVar);
		static void ScriptComponent_AddValueField_Float(uint64_t uuid, Coral::NativeString name, float floatVar);
		static void ScriptComponent_AddValueField_Double(uint64_t uuid, Coral::NativeString name, double doubleVar);
		static void ScriptComponent_AddValueField_Char(uint64_t uuid, Coral::NativeString name, char charVar);
		static void ScriptComponent_AddValueField_Bool(uint64_t uuid, Coral::NativeString name, bool boolVar);
		static void ScriptComponent_AddValueField_String(uint64_t uuid, Coral::NativeString name, Coral::NativeString stringVar);

		// CameraComponent2D
		static void CameraComponent2D_SetPositionX(uint64_t uuid, float x);
		static void CameraComponent2D_SetPositionY(uint64_t uuid, float y);

		static void CameraComponent2D_SetSizeX(uint64_t uuid, float size);
		static void CameraComponent2D_SetSizeY(uint64_t uuid, float size);

		static void CameraComponent2D_SetZoom(uint64_t uuid, float zoom);
		static void CameraComponent2D_SetRotation(uint64_t uuid, float rotation);
		static void CameraComponent2D_SetPrimary(uint64_t uuid, bool primary);

		static float CameraComponent2D_GetPositionX(uint64_t uuid);
		static float CameraComponent2D_GetPositionY(uint64_t uuid);

		static float CameraComponent2D_GetSizeX(uint64_t uuid);
		static float CameraComponent2D_GetSizeY(uint64_t uuid);

		static float CameraComponent2D_GetZoom(uint64_t uuid);
		static float CameraComponent2D_GetRotation(uint64_t uuid);
		static bool CameraComponent2D_GetPrimary(uint64_t uuid);

		// CameraComponent3D
		static void CameraComponent3D_SetPositionX(uint64_t uuid, float x);
		static void CameraComponent3D_SetPositionY(uint64_t uuid, float y);
		static void CameraComponent3D_SetPositionZ(uint64_t uuid, float z);

		static void CameraComponent3D_SetSizeX(uint64_t uuid, float size);
		static void CameraComponent3D_SetSizeY(uint64_t uuid, float size);

		static void CameraComponent3D_SetZoom(uint64_t uuid, float zoom);
		static void CameraComponent3D_SetRotation(uint64_t uuid, float rotation);
		static void CameraComponent3D_SetPrimary(uint64_t uuid, bool primary);

		static void CameraComponent3D_SetFOV(uint64_t uuid, float fov);

		static float CameraComponent3D_GetPositionX(uint64_t uuid);
		static float CameraComponent3D_GetPositionY(uint64_t uuid);
		static float CameraComponent3D_GetPositionZ(uint64_t uuid);

		static float CameraComponent3D_GetSizeX(uint64_t uuid);
		static float CameraComponent3D_GetSizeY(uint64_t uuid);

		static float CameraComponent3D_GetZoom(uint64_t uuid);
		static float CameraComponent3D_GetRotation(uint64_t uuid);
		static bool CameraComponent3D_GetPrimary(uint64_t uuid);

		static float CameraComponent3D_GetFOV(uint64_t uuid);

	};

}