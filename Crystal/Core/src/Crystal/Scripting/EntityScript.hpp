#pragma once

#include "Crystal/Core/Core.hpp"

#include <filesystem>

namespace Crystal
{

	class EntityScript
	{
	public:
		EntityScript() = default;
		EntityScript(std::filesystem::path path);
		virtual ~EntityScript();

		void SetDLL(std::filesystem::path path);
		void SetClass(const std::string& name);

		void OnCreate();
		void OnUpdate(Timestep& ts);
		// TODO(Jorben): Extra functionality (ex. Collision)

	private:
	};

}