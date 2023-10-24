#include "crpch.h"
#include "Renderer.hpp"

#include "Crystal/Renderer/RendererCommand.hpp"
#include "Crystal/Renderer/2D/Renderer2D.hpp"
#include "Crystal/Renderer/3D/Renderer3D.hpp"

namespace Crystal
{

	void Renderer::Init()
	{
		RendererCommand::Init();

		Renderer2D::Init();
		Renderer3D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
		Renderer3D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RendererCommand::SetViewPort(0, 0, width, height);
	}

}