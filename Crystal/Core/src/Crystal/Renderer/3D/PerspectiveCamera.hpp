#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Events.hpp"

namespace Crystal
{

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera();
		virtual ~PerspectiveCamera();

		void OnUpdate();
		void OnEvent(Event& e);
	};

}