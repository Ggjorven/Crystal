#include "GameLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Game/Settings.hpp"

GameLayer* GameLayer::s_Instance;	//Gets deleted in the engine because it's a layer

void GameLayer::OnAttach()
{
	s_Instance = this;

	//Application window (for width & height)
	Window& window = Application::Get().GetWindow();
	window.SetVSync(true);

	m_Camera = CreateRef<GameCamera>(window.GetWidth(), window.GetHeight(), true);
	m_Camera->SetMovementSpeed(1000.0f);

	//Entities::Init();
	Tiles::Init();

	m_TM = CreateScope<TileManager>();
	m_EM = CreateScope<MarioEntityManager>();

	LoadMap("assets/maps/world-1-1.txt");

	m_Camera->Init();

	RendererCommand::SetClearColour(glm::vec4(97.0f / 255.0f, 133.0f / 255.0f, 248.0f / 255.0f, 255.0f / 255.0f));
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Timestep& ts)
{
	//Update camera
	m_Camera->OnUpdate(ts);

	m_TM->OnUpdate(ts);
	m_EM->OnUpdate(ts);
}

void GameLayer::OnRender()
{
	m_TM->OnRender();
	m_EM->OnRender();
}

void GameLayer::OnImGuiRender()
{
	ImGui::Begin("Debug control");

	ImGui::Spacing();
	ImGui::DragInt("Global scale", (int*) &s_GlobalScale, 0.02f, 1, 6);
	ImGui::Spacing();

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Spacing();
	ImGui::DragFloat2("Camera position", (float*)glm::value_ptr(m_Camera->GetPosition()), 0.5f);
	ImGui::Spacing();

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	m_TM->OnImGuiRender();
	m_EM->OnImGuiRender();

	ImGui::End();
}

void GameLayer::OnEvent(Event& e)
{
	m_Camera->OnEvent(e);

	m_TM->OnEvent(e);
	m_EM->OnEvent(e);
}

void GameLayer::LoadMap(std::filesystem::path path)
{
	m_TM->LoadMap(path);
	m_EM->LoadMap(path);
}