#include "Mario.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Game/Settings.hpp"

Mario::Mario(const std::string_view& debugName, const glm::vec2& position, const glm::vec2& size)
	: Entity(debugName, position, size, s_MarioPath), m_CurrentTimer(0.f), m_State(State::None)
{
	m_TexCoords = TexCoords(0, 0, s_EntityWidth, s_EntityHeight);

	m_CoordChangeInterval = 0.175f;
}

Mario::~Mario()
{
}

void Mario::OnUpdate(Timestep& ts)
{
	m_State = State::None;

	Entity::OnUpdate(ts);

	if (Input::IsKeyPressed(CR_KEY_A)) 
	{ m_Position.x -= s_MarioSpeed * ts; m_State = State::Running; m_Reversed = true; }

	if (Input::IsKeyPressed(CR_KEY_S)) 
	{ m_Position.y += s_MarioSpeed * ts; m_State = State::Crouching; }

	if (Input::IsKeyPressed(CR_KEY_D)) 
	{ m_Position.x += s_MarioSpeed * ts; m_State = State::Running; m_Reversed = false; }

	if (Input::IsKeyPressed(CR_KEY_W)) 
	{ m_Position.y -= s_MarioSpeed * ts; m_State = State::Jumping; }


	//Ref<GameCamera> camera = GameLayer::GetSceneCamera();
	//camera->SetPosition({ camera->GetPosition().x + 0.05f, camera->GetPosition().y }); //CAMERA UPDATE FFS

	//Texture changing
	m_CurrentTimer.GetSeconds() += ts;
	switch (m_State) //TODO Crouching
	{
	case State::None:
		m_TexCoords.Y = s_EntityHeight * 0;
		break;

	case State::Running:
		m_TexCoords.Y = s_EntityHeight * 1;
		break;

	case State::Jumping:
		m_TexCoords.Y = s_EntityHeight * 2;
		break;
	}
	if (m_CurrentTimer >= m_CoordChangeInterval) //Check if need to update
	{
		m_CurrentTimer = 0;

		m_TexCoords.X += s_EntityWidth;
		if (m_TexCoords.X > s_EntityWidth * 2) m_TexCoords.X = 0; //There are 3 possible things but we start at 0 so 2
	}
}

void Mario::OnRender()
{
	Entity::OnRender();
}

void Mario::OnImGuiRender()
{
	ImGui::DragFloat("Mario's Speed", &s_MarioSpeed, 0.5f);

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::DragFloat2("Position", glm::value_ptr(m_Position), 0.5f);
	ImGui::DragFloat2("Size", glm::value_ptr(m_Size), 0.5f);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	/*
	ImGui::DragInt("Tex: X", &m_TexCoords.X, 0.5f, m_Texture->GetWidth() * -1, m_Texture->GetWidth());
	ImGui::DragInt("Tex: Y", &m_TexCoords.Y, 0.5f, m_Texture->GetHeight() * -1, m_Texture->GetHeight());
	ImGui::DragInt("Tex: Width", &m_TexCoords.Width, 0.5f, 0, m_Texture->GetWidth());
	ImGui::DragInt("Tex: Height", &m_TexCoords.Height, 0.5f, 0, m_Texture->GetHeight());
	*/
}

void Mario::OnEvent(Event& e)
{
	EventHandler handler(e);
}