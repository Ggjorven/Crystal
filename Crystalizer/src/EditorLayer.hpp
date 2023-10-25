#pragma once

#include <Crystal/Crystal.hpp>

#include <imgui.h>

#include "Sandbox/GameLayer.hpp"

using namespace Crystal;

class EditorLayer : public Layer
{
public:
	EditorLayer()
	{
		m_Layers.AddLayer(new GameLayer());
	}

	virtual ~EditorLayer() {}

	void OnAttach() override
	{
		Window& window = Application::Get().GetWindow();
		m_Buffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);
	}

	void OnUpdate(Timestep& ts)
	{
		for (auto layer : m_Layers)
			layer->OnUpdate(ts);
	}

	void OnRender() override
	{
		m_Buffer->Bind();
		//Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 100.0f, 100.0f }, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		for (auto layer : m_Layers)
			layer->OnRender();

		m_Buffer->Unbind();
	}

	void OnImGuiRender() override
	{
		//m_Buffer->BindTexture(0);
		ImGui::Begin("A");

		auto viewportSize = ImGui::GetContentRegionAvail();

		m_Buffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		ImGui::Image((void*)m_Buffer->GetColorAttachmentRendererID(), viewportSize, { 0, 1 }, { 1, 0 });

		ImGui::End();

		for (auto layer : m_Layers)
			layer->OnImGuiRender();
	}

private:
	LayerStack m_Layers;

	Ref<FrameBuffer> m_Buffer;
};