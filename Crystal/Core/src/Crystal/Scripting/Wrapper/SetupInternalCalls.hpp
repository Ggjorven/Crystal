#pragma once

#include "Crystal/Core/Core.hpp"

#include <Coral/Assembly.hpp>

namespace Crystal::Wrapper
{

	class Setup
	{
	public:
		static void Run(Coral::ManagedAssembly& assembly);
	};
}