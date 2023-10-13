#include "crpch.h"
#include "RendererCommand.hpp"

namespace Crystal
{

	Scope<RenderingAPI> RendererCommand::s_RenderingAPI = RenderingAPI::Create(); //Creates an instance of the proper RenderingAPI


	void RendererCommand::Init()
	{
		s_RenderingAPI->Init();
	}

	void RendererCommand::Clear()
	{
		s_RenderingAPI->Clear();
	}

	void RendererCommand::SetClearColour(const glm::vec4& colour)
	{
		s_RenderingAPI->SetClearColour(colour);
	}

	void RendererCommand::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RenderingAPI->SetViewPort(x, y, width, height);
	}

	void RendererCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		s_RenderingAPI->DrawIndexed(vertexArray);
	}

	void RendererCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader) 
	{
		s_RenderingAPI->DrawIndexed(vertexArray, shader);
	}

}