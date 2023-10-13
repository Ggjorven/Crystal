#include "crpch.h"
#include "Application.hpp"

#include <GLFW/glfw3.h>

#include "Crystal/Renderer/Renderer.hpp"
#include "Crystal/Renderer/RendererCommand.hpp"

namespace Crystal
{
	Application::Application(ApplicationInfo appInfo)
		: m_Running(true), m_AppInfo(appInfo)
	{
		Init(appInfo);
	}

	Application::~Application()
	{
		Renderer::Shutdown();

		for (Layer* layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<WindowCloseEvent>(CR_BIND_EVENT_FN(Application::OnWindowClose));
		handler.Handle<WindowResizeEvent>(CR_BIND_EVENT_FN(Application::OnWindowResize));

		for (Layer* layer : m_LayerStack)
			layer->OnEvent(e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//Delta Time
			float currentTime = (float)glfwGetTime();
			Timestep deltaTime(currentTime - m_LastTime);
			m_LastTime = currentTime;

			//Update & Render
			RendererCommand::Clear();
			m_Window->OnUpdate();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(deltaTime);
				layer->OnRender();
			}

			//ImGui
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnRender();
		}
	}

	void Application::AddLayer(Layer* layer)
	{
		m_LayerStack.AddLayer(layer);
	}

	void Application::AddOverlay(Layer* layer)
	{
		m_LayerStack.AddOverlay(layer);
	}

	void Application::Init(ApplicationInfo appInfo)
	{
		s_Instance = this;

		Log::Init();

		m_Window = Window::Create(appInfo.WindowProperties);
		m_Window->SetEventCallBack(CR_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		//Add ImGui
		m_ImGuiLayer = new BaseImGuiLayer();
		AddOverlay(m_ImGuiLayer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return true;
		}

		m_Minimized = false;

		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight()); //So the vertices say the same

		return false;
	}
}