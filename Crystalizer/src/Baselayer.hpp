#pragma once

#include <Crystal/Crystal.hpp>

#include <imgui.h>

//All editor layers

//Custom layers
#include "Sandbox/GameLayer.hpp"

using namespace Crystal;

class Baselayer : public Layer
{
public:
	Baselayer()
	{
		s_Instance = this;

		Window& window = Application::Get().GetWindow();
		m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);

		s_WindowMin.x = 0;
		s_WindowMin.y = 0;
		s_WindowMax.x = window.GetWidth();
		s_WindowMax.y = window.GetHeight();
	}

	void OnAttach() override
	{	
		AddLayer(new GameLayer());
	}

	void OnDetach() override
	{
	}

	void OnUpdate(Timestep& ts) override
	{
		for (Layer* layer : m_Layers)
			layer->OnUpdate(ts);
	}

	void OnRender()
	{
		// TODO: Framebuffer
		m_FrameBuffer->Bind();

		RendererCommand::Clear();

		for (Layer* layer : m_Layers)
			layer->OnRender();

		m_FrameBuffer->Unbind();
	}

	void OnImGuiRender() override
	{
		// TODO: Dockspace
		ImGui::DockSpaceOverViewport();
		//ImGui::Begin("Dockspace");
		//ImGui::End();

		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); //NECESSARY FOR RESIZING
			ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_None);

			ImVec2 size = ImGui::GetContentRegionAvail();
			m_FrameBuffer->Resize((uint32_t)size.x, (uint32_t)size.y);

			ImGui::Image((void*)m_FrameBuffer->GetColorAttachmentRendererID(), size, { 0, 1 }, { 1, 0 });

			//Update position vars
			s_WindowMin = ImGui::GetWindowContentRegionMin();
			s_WindowMax = ImGui::GetWindowContentRegionMax();

			s_WindowMin.x += ImGui::GetWindowPos().x;
			s_WindowMin.y += ImGui::GetWindowPos().y;
			s_WindowMax.x += ImGui::GetWindowPos().x;
			s_WindowMax.y += ImGui::GetWindowPos().y;

			ImGui::End();
			ImGui::PopStyleVar(1);
		}

		for (Layer* layer : m_Layers)
			layer->OnImGuiRender();
	}

	void OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<WindowResizeEvent>(CR_BIND_EVENT_FN(Baselayer::WindowResize)); //For when not using 

		for (Layer* layer : m_Layers)
			layer->OnEvent(e);
	}

public:
	static bool InWindow(MousePosition position) { return s_Instance->InWindowImplementation(position); }

private:
	void AddLayer(Layer* layer) { m_Layers.AddLayer(layer); }

	bool WindowResize(WindowResizeEvent& e)
	{
		//This function is for when a program asks for InWindow but there is no "Viewport" window so we use the actual window
		s_WindowMax.x = e.GetWidth();
		s_WindowMax.y = e.GetHeight();

		return false;
	}

	bool InWindowImplementation(MousePosition position)
	{
		CR_WARN("Mouse position X: {0}, Y: {1}", position.X, position.Y);
		CR_WARN("Window min: X: {0}, Y: {1}, max: X: {2}, Y: {3}", s_WindowMin.x, s_WindowMin.y, s_WindowMax.x, s_WindowMax.y);

		int safeZone = 5;
		if (
			position.X > s_WindowMin.x + safeZone && position.X < s_WindowMax.x - safeZone &&
			position.Y > s_WindowMin.y + safeZone && position.Y < s_WindowMax.y - safeZone
			)
		{
			//CR_WARN("TRUE");
			return true;
		}
		
		return false;
	}

private:
	static Baselayer* s_Instance;

private:
	LayerStack m_Layers;
	Ref<FrameBuffer> m_FrameBuffer;

	static ImVec2 s_WindowMin;
	static ImVec2 s_WindowMax;
};