#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

#include "Crystal/Renderer/RenderingAPI.hpp"
#include "Crystal/Renderer/VertexArray.hpp"
#include "Crystal/Renderer/Shader.hpp"

namespace Crystal
{

	//A class used to send the proper rendering commands to the proper rendering API
	class RendererCommand
	{
	public:
		static void Init();
		static void Clear();

		static void SetClearColour(const Vec4<float>& colour);
		static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void EnableDepth(bool enabled);

		static void DrawIndexed(const Ref<VertexArray>& vertexArray);
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader);

	private:
		static Scope<RenderingAPI> s_RenderingAPI;
	};

}