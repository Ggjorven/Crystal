#pragma once

#include "crpch.h"

#include "Crystal/Core/Core.hpp"
#include "Crystal/Events/Event.hpp"

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

		bool Vsync = false;
		EventCallBackFunction CallBack;

		WindowData(std::string name = "Crystal Window", uint32_t width = 1280, uint32_t height = 720/*, EventCallBackFunction func = ...*/)
			: Name(name), Width(width), Height(height)/*, CallBack(func)*/
		{
		}

		WindowData operator=(WindowProperties const& properties)
		{
			WindowData newData;
			newData.Name = properties.Name;
			newData.Width = properties.Width;
			newData.Height = properties.Height;
			//newData.CallBack = ...;
			return newData;
		}
	};



	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void SetEventCallBack(EventCallBackFunction func) = 0;

		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProperties properties = WindowProperties());
	};

}