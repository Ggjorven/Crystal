#include "GameCamera.hpp"

#include <Crystal/Core/Application.hpp>

#include <Crystal/Core/Events/Input/Input.hpp>
#include <Crystal/Core/Events/Codes/KeyCodes.hpp>

#include <vector>

#include "Game/Settings.hpp"
#include "GameLayer.hpp"

GameCamera::GameCamera(float width, float height, bool rotation)
	: m_Width(width), m_Height(height), m_Rotation(rotation), m_LastScale(s_GlobalScale)
{
	m_Camera = CreateRef<OrthoGraphicCamera>(-width / 2.0f * m_ZoomLevel, width / 2.0f * m_ZoomLevel, -height / 2.0f * m_ZoomLevel, height / 2.0f * m_ZoomLevel);

	m_Origin = { -(width / 2.0f), height / 2.0f };
}

GameCamera::~GameCamera()
{
}

void GameCamera::Init()
{
	/*
	float tileSize = (s_TileHeight * s_GlobalScale);

	m_CameraPosition = { m_CameraPosition.x, m_CameraPosition.y - tileSize, m_CameraPosition.z };
	m_Camera->SetPosition(m_CameraPosition);
	*/

	SetPositionToLowestTile();
}

void GameCamera::OnUpdate(Timestep& ts)
{
	if (Input::IsKeyPressed(CR_KEY_LEFT))
	{
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
	}
	else if (Input::IsKeyPressed(CR_KEY_RIGHT))
	{
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
	}

	if (Input::IsKeyPressed(CR_KEY_UP))
	{
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
	}
	else if (Input::IsKeyPressed(CR_KEY_DOWN))
	{
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
	}

	if (m_Rotation)
	{
		if (Input::IsKeyPressed(CR_KEY_KP_4))
			m_CameraRotation -= m_RotationSpeed * ts;

		if (Input::IsKeyPressed(CR_KEY_KP_6))
			m_CameraRotation += m_RotationSpeed * ts;

		//Reset
		if (Input::IsKeyPressed(CR_KEY_KP_5))
			m_CameraRotation = 0.0f;



		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera->SetRotation(m_CameraRotation);
	}

	Window& window = Application::Get().GetWindow();
	m_Origin = { -(window.GetWidth() / 2.0f), window.GetHeight() / 2.0f };

	m_Camera->SetPosition({ m_CameraPosition.x - m_Origin.x, m_CameraPosition.y - m_Origin.y, m_CameraPosition.z });

	if (m_LastScale != s_GlobalScale)
		SetPositionToLowestTile();
	m_LastScale = s_GlobalScale;

}

void GameCamera::OnEvent(Event& e)
{
	EventHandler dispatcher(e);

	dispatcher.Handle<MouseScrolledEvent>(CR_BIND_EVENT_FN(GameCamera::OnMouseScrolled));
	dispatcher.Handle<WindowResizeEvent>(CR_BIND_EVENT_FN(GameCamera::OnWindowResized));
}

bool GameCamera::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, m_MaxZoomLevel);

	float width = static_cast<float>(Application::Get().GetWindow().GetWidth()) / 2.0f;
	float height = static_cast<float>(Application::Get().GetWindow().GetHeight()) / 2.0f;

	m_Camera->SetProjection(-width * m_ZoomLevel, width * m_ZoomLevel, -height * m_ZoomLevel, height * m_ZoomLevel);

	SetPositionToLowestTile();

	return false;
}

bool GameCamera::OnWindowResized(WindowResizeEvent& e)
{
	float width = static_cast<float>(e.GetWidth()) / 2.0f;
	float height = static_cast<float>(e.GetHeight()) / 2.0f;

	//m_Origin = { -(width / 2.0f), height / 2.0f };

	m_Camera->SetProjection(-width * m_ZoomLevel, width * m_ZoomLevel, -height * m_ZoomLevel, height * m_ZoomLevel);

	SetPositionToLowestTile();

	return false;
}

void GameCamera::UpdateView()
{
	m_Camera->SetPosition({ m_CameraPosition.x - m_Origin.x, m_CameraPosition.y - m_Origin.y, m_CameraPosition.z });
}

void GameCamera::SetPositionToLowestTile()
{
	//CR_WARN("Called tile pos");

	//Check if lowest tile is in view
	std::vector<Scope<Tile>>& tiles = GameLayer::GetSceneTileManager()->GetTiles();

	glm::vec2& lowestPos = glm::vec2(0.0f, 0.0f);
	for (Scope<Tile>& tile : tiles)
	{
		//Get lowest position
		if (lowestPos.y < tile->GetPosition().y)
			lowestPos.y = tile->GetPosition().y;
	}

	//0.0f is middle
	//lowestPos.y is ~720, but we need half of this

	//float centerX = static_cast<float>(Application::Get().GetWindow().GetWidth()) / 2.0f;
	//float centerY = static_cast<float>(Application::Get().GetWindow().GetHeight()) / 2.0f;

	//float increment = (Application::Get().GetWindow().GetHeight() / 2.0f) - (lowestPos.y / 2.0f) + (s_TileHeight * s_GlobalScale);

	//CR_WARN("Change = (lowestPos.y * s_GlobalScale) - (s_TileHeight * s_GlobalScale) - windowSize = ?");
	
	Window& window = Application::Get().GetWindow();
	float windowSize = (float)window.GetHeight();
	//float change = (lowestPos.y * s_GlobalScale / windowSize) * (s_TileHeight * s_GlobalScale) * -1;
	float change = windowSize - (lowestPos.y * s_GlobalScale) - (s_TileHeight * s_GlobalScale);
	//-48
	//~110




	//CR_WARN("Window h: {0}", windowSize);
	//CR_WARN("Lowest t: {0}", lowestPos.y);
	//CR_WARN("Change = (lowestPos.y * s_GlobalScale) - (s_TileHeight * s_GlobalScale) - windowSize = ?");
	//CR_WARN("Change = ({0} * {1}) - ({2} * {3}) - {4} = {5}", lowestPos.y, s_GlobalScale, s_TileHeight, s_GlobalScale, windowSize, change);
	
	//TODO fix

	m_CameraPosition = { m_CameraPosition.x, change, m_CameraPosition.z};
	m_Camera->SetPosition(m_CameraPosition);
}