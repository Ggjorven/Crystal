#include "crpch.h"
#include "OpenGLRenderingAPI.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Core/Window.hpp"

#include "Crystal/Renderer/2D/Renderer2D.hpp"

namespace Crystal
{

	static void APIENTRY ErrorCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		CR_CORE_ERROR("[OpenGL]: type: {0}, id: {1}, severity: {2}, message: {3}", type, id, severity, message);
	}

	void OpenGLRenderingAPI::Init()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallBack, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &m_UnusedIds, true);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);
	}

	void OpenGLRenderingAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::SetClearColour(const Vec4<float>& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRenderingAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderingAPI::EnableDepth(bool enabled)
	{
		if (enabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRenderingAPI::EnableWireFrame(bool enabled)
	{
		if (enabled)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OpenGLRenderingAPI::ReplaceFramebuffer(Ref<FrameBuffer>& framebuffer)
	{
		const Window& window = Application::Get().GetWindow();

		glBlitNamedFramebuffer(framebuffer->GetRendererID(), 0,
			0, 0, framebuffer->GetWidth(), framebuffer->GetHeight(),
			0, 0, window.GetWidth(), window.GetHeight(),
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

	void OpenGLRenderingAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRenderingAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader)
	{
		shader->Bind();
		vertexArray->Bind();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}