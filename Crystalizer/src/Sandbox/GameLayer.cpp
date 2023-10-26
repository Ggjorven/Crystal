#include "GameLayer.hpp"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Editor.hpp"

void GameLayer::OnAttach()
{
	//Application window (for width & height)
	Window& window = Application::Get().GetWindow();
	window.SetVSync(true);

	m_Camera2D = CreateRef<Camera2D>(window.GetWidth(), window.GetHeight());
	m_Camera2D->SetOrigin({ window.GetWidth() / 2.0f * -1, window.GetHeight() / 2.0f });
	m_Camera2D->SetMovementSpeed(1000.0f);

	m_Camera3D = CreateRef<Camera3D>(window.GetWidth(), window.GetHeight());

	RendererCommand::SetClearColour(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Timestep& ts)
{
	m_Camera2D->OnUpdate(ts);
	m_Camera3D->OnUpdate(ts);

	//For ImGui window resizing //ggjorven for resizing
	glm::vec2 size = EditorLayer::GetWindowSize();

	float zoom = m_Camera2D->GetZoomLevel();
	m_Camera2D->GetCamera()->SetProjection(-size.x / 2.0f * zoom, size.x / 2.0f * zoom, -size.y / 2.0f * zoom, size.y / 2.0f * zoom);
	m_Camera2D->SetOrigin({ size.x / 2.0f * -1, size.y / 2.0f });

	m_Camera3D->GetCamera()->SetProjectionMatrix(glm::perspective(glm::radians(45.0f), size.x / size.y, 0.1f, 100.0f));
}

void GameLayer::OnRender()
{
	Renderer3D::DrawCube(glm::vec3(2.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false, m_Camera3D->GetCamera());

	if (m_UseTex && m_Tex)
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 64.f, 64.f }, { 32.0f, -32.0f }, m_Tex, false, m_Camera2D->GetCamera());
	else
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 64.f, 64.f }, { 32.0f, -32.0f }, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), false, m_Camera2D->GetCamera());
}

void GameLayer::OnImGuiRender()
{
	ImGui::Begin("Editor");

	Panels::TexturePanel("Texture", m_Tex, &m_UseTex);

	ImGui::End();
}

void GameLayer::OnEvent(Event& e)
{
	EventHandler handler(e);

	handler.Handle<MouseButtonPressedEvent>(CR_BIND_EVENT_FN(GameLayer::MousePressImGui));
	handler.Handle<WindowResizeEvent>(CR_BIND_EVENT_FN(GameLayer::WindowResize));

	if (e.Handled)
		return;

	m_Camera2D->OnEvent(e);
	m_Camera3D->OnEvent(e);
}

bool GameLayer::MousePressImGui(MouseButtonPressedEvent& e)
{
	//ImGuiIO io = ImGui::GetIO();

	MousePosition mousePosition = Input::GetMousePosition();

	if (e.GetMouseButton() == CR_MOUSE_BUTTON_LEFT && !EditorLayer::InWindow(mousePosition)) // TODO: Fix
		return true;

	return false;
}

bool GameLayer::WindowResize(WindowResizeEvent& e)
{
	m_Camera2D->SetOrigin({ e.GetWidth() / 2.0f * -1, e.GetHeight() / 2.0f });

	return false;
}
