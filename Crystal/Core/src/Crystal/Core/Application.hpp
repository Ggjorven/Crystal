#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/Events/Event.hpp"
#include "Crystal/Core/Events/ApplicationEvent.hpp"
#include "Crystal/Core/Events/KeyEvent.hpp"
#include "Crystal/Core/Events/MouseEvent.hpp"

#include "Crystal/Core/Window.hpp"

#include "Crystal/Core/Layer.hpp"
#include "Crystal/Core/Layerstack.hpp"

#include "Crystal/ImGui/BaseImGuiLayer.hpp"

#include <filesystem>

namespace Crystal
{

	struct ApplicationInfo
	{
	public:
		WindowProperties WindowProperties;
		int ArgCount;
		char** Args;

		ApplicationInfo(Crystal::WindowProperties windowProperties = Crystal::WindowProperties())
			: WindowProperties(windowProperties), ArgCount(0), Args(nullptr)
		{
		}
	};

	class Application
	{
	public:
		Application(ApplicationInfo appInfo);
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();
		inline void Close() { m_Running = false; }

		void AddLayer(Layer* layer);
		void AddOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		template<typename TEvent>
		inline void DispatchEvent(TEvent e = TEvent()) { static_assert(std::is_base_of<Event, TEvent>::value); OnEvent(e); }

		inline static Application& Get() { return *s_Instance; }
		inline static std::filesystem::path GetWorkingDirectory() { return std::filesystem::path(s_Instance->m_AppInfo.Args[0]).parent_path(); }

	private:
		void Init(ApplicationInfo appInfo);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationInfo m_AppInfo;

		Scope<Window> m_Window;
		bool m_Running;
		bool m_Minimized;

		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;

		BaseImGuiLayer* m_ImGuiLayer;

		//For deltatime
		float m_LastTime;
	};



	Application* CreateApplication(int argc, char* argv[]);

}