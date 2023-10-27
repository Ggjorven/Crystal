#pragma once

#include "Crystal/Core/Window.hpp"

#include <GLFW/glfw3.h>

#include "Renderer/GraphicsContext.hpp"

namespace Crystal
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties properties);
		virtual ~WindowsWindow();

		void SetEventCallBack(EventCallBackFunction func) override { m_Data.CallBack = func; }

		void OnUpdate() override;
		void OnRender() override;

		//Window
		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		//Viewport
		bool InView(MousePosition position) const override;

		uint32_t GetViewportX() const override { return m_Data.ViewX; }
		uint32_t GetViewportY() const override { return m_Data.ViewY; }

		void SetViewportX(uint32_t x) override { m_Data.ViewX = x; }
		void SetViewportY(uint32_t y) override { m_Data.ViewY = y; }

		uint32_t GetViewportWidth() const override { return m_Data.ViewWidth; }
		uint32_t GetViewportHeight() const override { return m_Data.ViewHeight; }

		void SetViewportWidth(uint32_t width) override { m_Data.ViewWidth = width; }
		void SetViewportHeight(uint32_t height) override { m_Data.ViewHeight = height; }


		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return m_Data.Vsync; }

		void* GetNativeWindow() const override { return (void*)m_Window; }

	private:
		bool Init(WindowProperties properties);
		void Shutdown();

		static void ErrorCallBack(int errorCode, const char* description);

	private:
		static bool s_GLFWinitialized;
		static uint32_t s_Instances;

		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;
		WindowData m_Data;

	};
}