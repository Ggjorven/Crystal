#include "Entity.hpp"

#include "Game/Settings.hpp"

#include "GameLayer.hpp"

Entity::Entity(const std::string_view& debugName, const glm::vec2& position, const glm::vec2& size, std::filesystem::path texturePath)
	: m_DebugName(debugName), m_Position(position), m_Size(size), m_Reversed(false), m_Texture(Texture2D::Create(texturePath.string()))
{
	m_TexCoords = TexCoords(0, 0, m_Texture->GetWidth(), m_Texture->GetHeight());
}

void Entity::OnUpdate(Timestep& ts)
{
}

void Entity::OnRender()
{
	Renderer2D::DrawQuad({ m_Position.x * s_GlobalScale, m_Position.y * -1.0f * s_GlobalScale }, { m_Size.x * s_GlobalScale, m_Size.y * s_GlobalScale }, { m_Size.x / 2.0f * s_GlobalScale, -(m_Size.y / 2.0f * s_GlobalScale) }, m_Texture, m_TexCoords, m_Reversed, GameLayer::GetSceneCamera()->GetCamera());
}