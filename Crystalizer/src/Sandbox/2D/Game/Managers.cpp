#include "Managers.hpp"

#include "Settings.hpp"

#include <fstream>
#include <sstream>

EntityManager::EntityManager()
	: m_InsertIndex(0)
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::OnUpdate(Timestep& ts) //TODO check if in view
{
	for (Scope<Entity>& MarioEntity : m_Entities)
		MarioEntity->OnUpdate(ts);
}

void EntityManager::OnRender()
{
	for (Scope<Entity>& MarioEntity : m_Entities)
		MarioEntity->OnRender();
}

void EntityManager::OnImGuiRender()
{
	for (Scope<Entity>& MarioEntity : m_Entities)
		MarioEntity->OnImGuiRender();
}

void EntityManager::OnEvent(Event& e)
{
	for (Scope<Entity>& MarioEntity : m_Entities)
		MarioEntity->OnEvent(e);
}

void EntityManager::LoadMap(std::filesystem::path path)
{
	//Reset
	m_Entities.clear();

	//Open file
	std::ifstream file(path);
	std::string string;

	if (!file.good())
		CR_ERROR("Failed to load: {0}", path.string());

	//Read raw map data
	while (std::getline(file, string))
		m_RawMap.emplace_back(string);

	//Convert to tiles
	glm::vec2 pos = { 0.0f, 0.0f };

	for (std::string& line : m_RawMap)
	{
		pos.x = 0;
		for (char& MarioEntity : line) //MarioEntity (X)
		{
			CharToEntity(MarioEntity, pos);
			pos.x += s_EntityWidth;
		}
		pos.y += s_EntityHeight;
	}
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
	std::string string;

	if (!file.good())
		CR_ERROR("Failed to load: {0}", path.string());

	//Read raw map data
	while (std::getline(file, string))
		m_RawMap.emplace_back(string);

	//Convert to tiles
	glm::vec2 pos = { 0.0f, 0.0f };

	for (std::string& line : m_RawMap)
	{
		pos.x = 0;
		for (char& tile : line) //MarioEntity (X)
		{
			CharToTile(tile, pos);
			pos.x += s_TileWidth;
		}
		pos.y += s_TileHeight;
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
