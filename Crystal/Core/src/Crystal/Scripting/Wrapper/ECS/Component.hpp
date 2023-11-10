#pragma once

// Note(Jorben): Since C# doesn't support direct import/export of templated functions, we have to recreate these functions for every templated type as a standalone function.

#include "Crystal/ECS/Component.hpp"

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
	};

}