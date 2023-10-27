#include "GameLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void GameLayer::OnAttach()
{
	//Application window (for width & height)
	Window& window = Application::Get().GetWindow();
	window.SetVSync(true);

	m_Camera2D = CreateRef<Camera2D>(window.GetWidth(), window.GetHeight());
	m_Camera2D->SetOrigin({ window.GetWidth() / 2.0f * -1, window.GetHeight() / 2.0f });

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
}

void GameLayer::OnRender()
{
	Renderer3D::DrawCube(glm::vec3(2.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false, m_Camera3D->GetCamera());

	Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 64.f, 64.f }, { 0.0f, 0.0f }, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), false, m_Camera2D->GetCamera());
}

void GameLayer::OnImGuiRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("Dockspace", (bool*)0, ImGuiWindowFlags_NoDocking);
	ImGui::DockSpace(1);
	ImGui::End();

	ImGui::PopStyleVar(1);

	ImGui::Begin("Debug control");

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
	ImGuiIO io = ImGui::GetIO();

	if (e.GetMouseButton() == CR_MOUSE_BUTTON_LEFT && io.WantCaptureMouse)
		return true;

	return false;
}

bool GameLayer::WindowResize(WindowResizeEvent& e)
{
	m_Camera2D->SetOrigin({ e.GetWidth() / 2.0f * -1, e.GetHeight() / 2.0f });

	return false;
}
