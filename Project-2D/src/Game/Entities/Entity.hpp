#pragma once

#include <string>
#include <filesystem>

#include <glm/glm.hpp>

#include <Crystal/Crystal.hpp>

using namespace Crystal;

class Entity
{
public:
	Entity(const std::string_view& debugName, const glm::vec2& position, const glm::vec2& size, std::filesystem::path texturePath);
	virtual ~Entity() = default;

	virtual void OnUpdate(Timestep& ts);
	virtual void OnRender();
	virtual void OnImGuiRender() = 0;

	virtual void OnEvent(Event& e) = 0;

	inline virtual glm::vec2& GetPosition() { return m_Position; }
	inline virtual glm::vec2& GetSize() { return m_Size; }
	inline virtual Ref<Texture2D>& GetTexture() { return m_Texture; }
	inline virtual TexCoords& GetTexCoords() { return m_TexCoords; }

protected:
	std::string m_DebugName;

protected:
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	bool m_Reversed;

	Ref<Texture2D> m_Texture;
	TexCoords m_TexCoords;
};