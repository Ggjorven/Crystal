#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/UUID.hpp"

#include <Coral/Core.hpp>
#include <Coral/FieldInfo.hpp>
#include <Coral/Memory.hpp>
#include <Coral/Assembly.hpp>

#include <unordered_map>

namespace Crystal::Wrapper
{

	typedef CR_UUID SceneID;

	class Scene
	{
	public:
		static uint64_t GetUUIDByTag(Coral::NativeString tag);

	private:
		static std::unordered_map<SceneID, std::unordered_map<std::string, CR_UUID>> s_UUIDCache;
	};

}