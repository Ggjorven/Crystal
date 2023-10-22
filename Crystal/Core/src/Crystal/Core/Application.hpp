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

namespace Crystal
{

	struct ApplicationInfo
	{
	public:
		WindowProperties WindowProperties;


		ApplicationInfo(Crystal::WindowProperties windowProperties = Crystal::WindowProperties())
			: WindowProperties(windowProperties)
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

		inline static Application& Get() { return *s_Instance; }

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