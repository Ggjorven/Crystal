#include "crpch.h"
#include "Window.hpp"

#include "Crystal/Renderer/Renderer.hpp"
#include "Crystal/Renderer/RenderingAPI.hpp"

#include "Crystal/Platforms/Windows/WindowsWindow.hpp"

namespace Crystal
{
	Scope<Window> Window::Create(const WindowProperties properties)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_CRITICAL("No proper rendering API selected!");
		case RenderingAPI::API::OpenGL: return CreateScope<WindowsWindow>(properties);
		}

		return nullptr;
	}
}