#pragma once

#include <Crystal/Crystal.hpp>

#include <string>
#include <vector>

#include "Entities/Entity.hpp"
#include "Entities/Goomba.hpp"
#include "Entities/Mario.hpp"

using namespace Crystal;

class EntityManager
{
public:
	EntityManager();
	virtual ~EntityManager();

	virtual void OnUpdate(Timestep& ts);
	virtual void OnRender();
	virtual void OnImGuiRender();

	virtual void OnEvent(Event& e);

	void LoadMap(std::filesystem::path path);

	inline std::vector<Scope<Entity>>& GetEntities() { return m_Entities; }
	inline std::vector<std::string>& GetRawMap() { return m_RawMap; }

private:
	void CharToEntity(char c, const glm::vec2& position);

private:
	std::vector<std::string> m_RawMap;
	std::vector<Scope<Entity>> m_Entities;
	int32_t m_InsertIndex;
};



#include "Tiles/Tile.hpp"

class TileManager
{
public:
	TileManager();
	virtual ~TileManager();

	virtual void OnUpdate(Timestep& ts);
	virtual void OnRender();
	virtual void OnImGuiRender();

	virtual void OnEvent(Event& e);

	void LoadMap(std::filesystem::path path);

	inline std::vector<Scope<Tile>>& GetTiles() { return m_Tiles; }
	inline std::vector<std::string>& GetRawMap() { return m_RawMap; }

private:
	void CharToTile(char c, const glm::vec2& position);

private:
	std::vector<std::string> m_RawMap;
	std::vector<Scope<Tile>> m_Tiles;
	int32_t m_InsertIndex;

};