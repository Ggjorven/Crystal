#include "Tile.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Game/Settings.hpp"
#include "GameLayer.hpp"

Ref<Texture2D> Tiles::s_GroundTexture;
TexCoords Tiles::s_GroundCoords;

Tile::Tile(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D>& texture, TexCoords coords)
	: m_Position(position), m_Size(size), m_Texture(texture), m_TexCoords(coords)
{
	//m_TexCoords = TexCoords(0, 0, m_Texture->GetWidth(), m_Texture->GetHeight());
	//CR_WARN("Position: x: {0}, y: {1}", position.x, position.y);
}

Tile::~Tile()
{
}

void Tile::OnUpdate(Timestep& ts)
{
}

void Tile::OnRender()
{
	Renderer2D::DrawQuad({ m_Position.x * s_GlobalScale, m_Position.y * -1.0f * s_GlobalScale }, { m_Size.x * s_GlobalScale, m_Size.y * s_GlobalScale }, { m_Size.x / 2.0f * s_GlobalScale, -(m_Size.y / 2.0f * s_GlobalScale) }, m_Texture, m_TexCoords, false, GameLayer::GetSceneCamera()->GetCamera());
}

void Tile::OnImGuiRender()
{
	/*
	ImGui::Text("Tile");

	ImGui::DragFloat2("position", glm::value_ptr(m_Position), 0.5f);
	ImGui::DragFloat2("size", glm::value_ptr(m_Size), 0.5f);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	*/
}

void Tile::OnEvent(Event& e)
{
}



void Tiles::Init()
{
	s_GroundTexture = Crystal::Texture2D::Create(s_GroundPath);
	s_GroundCoords = s_GroundTexCoords;
}