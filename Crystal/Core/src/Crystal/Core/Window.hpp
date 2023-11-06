#pragma once

#include <string>
#include <functional>

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

namespace Crystal
{

	using EventCallBackFunction = std::function<void(Event&)>;



	struct WindowProperties
	{
		std::string Name;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(std::string name = "Crystal Window", uint32_t width = 1280, uint32_t height = 720)
			: Name(name), Width(width), Height(height)
		{
		}
	};

	struct WindowData
	{
		std::string Name;
		uint32_t Width;
		uint32_t Height;

		uint32_t ViewX;
		uint32_t ViewY;
		uint32_t ViewWidth;
		uint32_t ViewHeight;
		

		bool Vsync = false;
		EventCallBackFunction CallBack;

		WindowData(std::string name = "Crystal Window", uint32_t width = 1280, uint32_t height = 720/*, EventCallBackFunction func = ...*/)
			: Name(name), Width(width), Height(height), ViewX(0), ViewY(0), ViewWidth(width), ViewHeight(height)/*, CallBack(func)*/
		{
		}

		WindowData operator=(WindowProperties const& properties)
		{
			WindowData newData;
			newData.Name = properties.Name;
			newData.Width = properties.Width;
			newData.Height = properties.Height;
			return newData;
		}
	};

	struct MousePosition;

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void SetEventCallBack(EventCallBackFunction func) = 0;

		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;

		// Actual window size
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Viewport is different in editor compared to runtime
		virtual void SetViewportX(uint32_t x) = 0;
		virtual void SetViewportY(uint32_t y) = 0;

		virtual uint32_t GetViewportX() const = 0;
		virtual uint32_t GetViewportY() const = 0;

		virtual uint32_t GetViewportWidth() const = 0;
		virtual uint32_t GetViewportHeight() const = 0;

		virtual void SetViewportWidth(uint32_t width) = 0;
		virtual void SetViewportHeight(uint32_t height) = 0;

		/*
			Adds a bit of padding (in non-Dist builds)...
		*/
		virtual bool InView(MousePosition position) const = 0;

		// Extra
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProperties properties = WindowProperties());
	};

}