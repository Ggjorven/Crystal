#pragma once

#include <Crystal/Crystal.hpp>

#include <imgui.h>

using namespace Crystal;

class EditorLayer : public Layer
{
public:
	EditorLayer()
	{
	}

	virtual ~EditorLayer() {}

	void OnAttach() override
	{
		Window& window = Application::Get().GetWindow();
		m_Buffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);
	}

	void OnRender() override
	{
		m_Buffer->Bind();
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 100.0f, 100.0f }, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
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
	}

private:
	Ref<FrameBuffer> m_Buffer;
};