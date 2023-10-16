#include "Managers.hpp"

#include "Settings.hpp"

#include <fstream>
#include <string>
#include <sstream>

EntityManager::EntityManager()
	: m_InsertIndex(0)
{
	LoadMap("assets/maps/world-1-1.txt");
}

EntityManager::~EntityManager()
{
}

void EntityManager::OnUpdate(Timestep& ts) //TODO check if in view
{
	for (Scope<Entity>& entity : m_Entities)
		entity->OnUpdate(ts);
}

void EntityManager::OnRender()
{
	for (Scope<Entity>& entity : m_Entities)
		entity->OnRender();
}

void EntityManager::OnImGuiRender()
{
	for (Scope<Entity>& entity : m_Entities)
		entity->OnImGuiRender();
}

void EntityManager::OnEvent(Event& e)
{
	for (Scope<Entity>& entity : m_Entities)
		entity->OnEvent(e);
}

void EntityManager::LoadMap(std::filesystem::path path)
{
	//Reset
	m_Entities.clear();

	CharToEntity('p', glm::vec2(0.0f, 0.0f));
}

void EntityManager::CharToEntity(char c, const glm::vec2& position)
{
	switch (c)
	{
	case 'p':
		m_Entities.emplace_back(CreateScope<Mario>("Mario", position, glm::vec2(s_EntityWidth, s_EntityHeight)));
		break;

	case 'g':
		//m_Entities.emplace(m_Entities.begin() + m_InsertIndex++, Goomba());
		break;
	}
}



TileManager::TileManager()
	: m_InsertIndex(0)
{
	LoadMap("assets/maps/world-1-1.txt");
}

TileManager::~TileManager()
{
}

void TileManager::OnUpdate(Timestep& ts)
{
	for (Scope<Tile>& tile : m_Tiles)
		tile->OnUpdate(ts);
}

void TileManager::OnRender()
{
	for (Scope<Tile>& tile : m_Tiles)
		tile->OnRender();
}

void TileManager::OnImGuiRender()
{
	for (Scope<Tile>& tile : m_Tiles)
		tile->OnImGuiRender();
}

void TileManager::OnEvent(Event& e)
{
	for (Scope<Tile>& tile : m_Tiles)
		tile->OnEvent(e);
}

void TileManager::LoadMap(std::filesystem::path path)
{
	//Reset
	m_Tiles.clear();

	//Open file
	std::ifstream file(path);
	std::vector<std::string> rawMap;
	std::string string;

	if (!file.good())
		CR_ERROR("Failed to load: {0}", path.string());

	//Read raw map data
	while (std::getline(file, string))
		rawMap.emplace_back(string);

	//Convert to tiles
	glm::vec2 pos = { 0.0f, 0.0f };

	for (std::string& line : rawMap)
	{
		pos.x = 0;
		for (char& tile : line) //Entity (X)
		{
			CharToTile(tile, pos);
			pos.x += s_TileWidth * s_GlobalScale;
		}
		pos.y += s_TileHeight * s_GlobalScale;
	}
}

void TileManager::CharToTile(char c, const glm::vec2& position)
{
	switch (c)
	{
	case '#':
		m_Tiles.emplace(m_Tiles.begin() + m_InsertIndex++, CreateScope<Tile>(position, glm::vec2(s_TileWidth, s_TileHeight), Tiles::s_GroundTexture, Tiles::s_GroundCoords));
		break;

	case '-':
		//m_Tiles.emplace(m_InsertIndex++, Tile());
		break;
	}
}
