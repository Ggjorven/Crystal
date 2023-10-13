#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

#include "Crystal/Renderer/VertexArray.hpp"
#include "Crystal/Renderer/Shader.hpp"

namespace Crystal
{

	class RenderingAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL, Vulkan
		};

	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColour(const glm::vec4& colour) = 0;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader) = 0;

		inline static API GetAPI() { return s_API; }

		static Scope<RenderingAPI> Create();

	private:
		static API s_API;
	};

}