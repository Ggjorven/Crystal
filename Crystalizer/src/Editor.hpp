#pragma once

#include <Crystal/Crystal.hpp>

#include <imgui.h>

//All editor layers
#include "Panels/Panels.hpp"

//Custom layers
#include "Sandbox/GameLayer.hpp"

using namespace Crystal;

class EditorLayer : public Layer
{
public:
	EditorLayer(const ApplicationInfo& appinfo)
	{
		s_Instance = this;

		Window& window = Application::Get().GetWindow();
		m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);

		s_WindowMin.x = 0.0f;
		s_WindowMin.y = 0.0f;
		s_WindowMax.x = (float)window.GetWidth();
		s_WindowMax.y = (float)window.GetHeight();
	}

	void OnAttach() override
	{	
		Panels::Init();

		Ref<Scene> scene = CreateRef<Scene>("testScene");
		SceneSerializer serializer(scene);

		serializer.Serialize("test.yaml");
		serializer.Deserialize("test.yaml");

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
		//RendererCommand::SetViewPort(0, 0, s_WindowMax.x, s_WindowMax.y);
		m_FrameBuffer->Bind();

		RendererCommand::Clear();
		//RendererCommand::SetViewPort(0, 0, s_WindowMax.x, s_WindowMax.y);

		for (Layer* layer : m_Layers)
			layer->OnRender();

		//RendererCommand::SetViewPort(0, 0, s_WindowMax.x, s_WindowMax.y);

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
			//m_FrameBuffer->Resize(1280u, 720u);

			ImGui::Image((void*)m_FrameBuffer->GetColorAttachmentRendererID(), size, { 0, 1 }, { 1, 0 });

			//Update position vars
			s_WindowMin = ImGui::GetWindowContentRegionMin();
			s_WindowMax = ImGui::GetWindowContentRegionMax();

			//s_WindowMin.x += ImGui::GetWindowPos().x;
			//s_WindowMin.y += ImGui::GetWindowPos().y;
			//s_WindowMax.x += ImGui::GetWindowPos().x;
			//s_WindowMax.y += ImGui::GetWindowPos().y;

			ImGui::End();
			ImGui::PopStyleVar(1);
		}

		for (Layer* layer : m_Layers)
			layer->OnImGuiRender();
	}

	void OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<WindowResizeEvent>(CR_BIND_EVENT_FN(EditorLayer::WindowResize)); //For when not using 

		for (Layer* layer : m_Layers)
			layer->OnEvent(e);
	}

public:
	static bool InWindow(MousePosition position) { return s_Instance->InWindowImplementation(position); }
	static glm::vec2 GetWindowSize() { return { s_WindowMax.x, s_WindowMax.y }; }

private:
	void AddLayer(Layer* layer) { m_Layers.AddLayer(layer); }

	bool WindowResize(WindowResizeEvent& e)
	{
		//This function is for when a program asks for InWindow but there is no "Viewport" window so we use the actual window
		s_WindowMax.x = (float)e.GetWidth();
		s_WindowMax.y = (float)e.GetHeight();

		return false;
	}

	bool InWindowImplementation(MousePosition position)
	{
		//CR_WARN("Mouse position X: {0}, Y: {1}", position.X, position.Y);
		//CR_WARN("Window min: X: {0}, Y: {1}, max: X: {2}, Y: {3}", s_WindowMin.x, s_WindowMin.y, s_WindowMax.x, s_WindowMax.y);

		int safeZone = 5;
		if (
			position.X >= s_WindowMin.x + safeZone && position.X <= s_WindowMax.x - safeZone &&
			position.Y >= s_WindowMin.y + safeZone && position.Y <= s_WindowMax.y - safeZone
			)
		{
			//CR_WARN("TRUE");
			return true;
		}
		
		return false;
	}

private:
	static EditorLayer* s_Instance;

private:
	LayerStack m_Layers;
	Ref<FrameBuffer> m_FrameBuffer;

	Ref<Texture2D> m_Tex;
	bool m_UseTex = false;

	static ImVec2 s_WindowMin;
	static ImVec2 s_WindowMax;
};