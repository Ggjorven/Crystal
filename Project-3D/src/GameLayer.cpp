#include "GameLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void GameLayer::OnAttach()
{
	//Application window (for width & height)
	Window& window = Application::Get().GetWindow();
	window.SetVSync(true);

	RendererCommand::SetClearColour(glm::vec4(97.0f / 255.0f, 133.0f / 255.0f, 248.0f / 255.0f, 255.0f / 255.0f));
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Timestep& ts)
{
}

void GameLayer::OnRender()
{
}

void GameLayer::OnImGuiRender()
{
	ImGui::Begin("Debug control");

	ImGui::End();
}

void GameLayer::OnEvent(Event& e)
{

}