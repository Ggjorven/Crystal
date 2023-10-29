#pragma once

#include <Crystal/Crystal.hpp>

#include <imgui.h>

//All editor layers
#include "Panels/Panels.hpp"

//Custom layers
#include "Sandbox/2D/Layer2D.hpp"
#include "Sandbox/3D/Layer3D.hpp"

using namespace Crystal;

class EditorLayer : public Layer
{
public:
	EditorLayer(const ApplicationInfo& appinfo)
	{
		Window& window = Application::Get().GetWindow();
		window.SetVSync(true);

		m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);
	}

	void OnAttach() override
	{	
		Panels::Init();

		//Ref<Scene> scene = CreateRef<Scene>("testScene");
		//SceneSerializer serializer(scene);

		//serializer.Serialize("test.yaml");
		//serializer.Deserialize("test.yaml");

		//AddLayer(new Layer2D());
		AddLayer(new Layer3D());
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
		m_FrameBuffer->Bind();

		for (Layer* layer : m_Layers)
			layer->OnRender();

		m_FrameBuffer->Unbind();
	}

	void OnImGuiRender() override
	{
		ImGui::DockSpaceOverViewport();

		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); //NECESSARY FOR RESIZING
			ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_None);

			ImVec2 size = ImGui::GetContentRegionAvail();
			if (size.x != 0 || size.y != 0) //Check if window is collapsed
				m_FrameBuffer->Resize((uint32_t)size.x, (uint32_t)size.y);

			ImGui::Image((void*)m_FrameBuffer->GetColorAttachmentRendererID(), size, { 0, 1 }, { 1, 0 });

			//Update viewport size
			Window& window = Application::Get().GetWindow();

			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
			ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

			window.SetViewportWidth(ImGui::GetWindowSize().x);
			window.SetViewportHeight(ImGui::GetWindowSize().y);
			window.SetViewportX(relativePos.x);
			window.SetViewportY(relativePos.y);

			ImGui::End();
			ImGui::PopStyleVar(1);

			ImGui::Begin("Metrics");

			ImGuiIO io = ImGui::GetIO();
			ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);

			ImGui::End();
		}

		for (Layer* layer : m_Layers)
			layer->OnImGuiRender();
	}

	void OnEvent(Event& e)
	{
		for (Layer* layer : m_Layers)
			layer->OnEvent(e);
	}

private:
	void AddLayer(Layer* layer) { m_Layers.AddLayer(layer); }

private:
	LayerStack m_Layers;
	Ref<FrameBuffer> m_FrameBuffer;

	Ref<Texture2D> m_Tex;
	bool m_UseTex = false;
};