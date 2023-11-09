#pragma once

// Note(Jorben): Since C# doesn't support direct import/export of templated functions, we have to recreate these functions for every templated type as a standalone function.

#include "Crystal/ECS/Component.hpp"

namespace Crystal::Wrapper
{

	class Entity
	{
	public:
		static void AddTagComponent(uint64_t uuid, Coral::NativeString tag);
	};


}