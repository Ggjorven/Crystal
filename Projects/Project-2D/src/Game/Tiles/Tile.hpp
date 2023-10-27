#pragma once

#include <string>

#include <glm/glm.hpp>

#include <Crystal/Crystal.hpp>

using namespace Crystal;

class Tile
{
public:
	Tile(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D>& texture, TexCoords coords);
	virtual ~Tile();

	virtual void OnUpdate(Timestep& ts);
	virtual void OnRender();
	virtual void OnImGuiRender();

	virtual void OnEvent(Event& e);

	inline glm::vec2& GetPosition() { return m_Position; }

private:
	glm::vec2 m_Position;
	glm::vec2 m_Size;

	Ref<Texture2D>& m_Texture;
	TexCoords m_TexCoords;
};

class Tiles
{
public:
	static void Init();



	static Ref<Texture2D> s_GroundTexture;
	static TexCoords s_GroundCoords;
};