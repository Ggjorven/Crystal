#include "crpch.h"
#include "WindowWrapper.hpp"

#include "Crystal/Core/Application.hpp"

namespace Crystal::Wrapper
{

	uint32_t Window::Window_GetWindowWidth()
	{
		return Application::Get().GetWindow().GetViewportWidth();
	}

	uint32_t Window::Window_GetWindowHeight()
	{
		return Application::Get().GetWindow().GetViewportHeight();
	}

}