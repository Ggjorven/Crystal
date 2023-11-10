#pragma once

// Note(Jorben): Since C# doesn't support direct import/export of templated functions, we have to recreate these functions for every templated type as a standalone function.
#include "Crystal/Utils/CustomTypes.hpp"
#include "Crystal/ECS/Component.hpp"

namespace Crystal::Wrapper
{

	class Entity
	{
	public:
		static void AddTagComponent(uint64_t uuid, Coral::NativeString tag);
		static void AddTransformComponent(uint64_t uuid, Vec3<float> position, Vec3<float> size, float rotation);
	};


}