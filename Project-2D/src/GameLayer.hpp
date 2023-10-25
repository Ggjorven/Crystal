#pragma once

#include <Crystal/Crystal.hpp>

#include <filesystem>

#include "Game/Managers.hpp"
#include "Game/Utils/GameCamera.hpp"

using namespace Crystal;

class GameLayer : public Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Timestep& ts) override;
	void OnRender() override;
	void OnImGuiRender() override;

	void OnEvent(Event& e);

	inline const Ref<GameCamera>& GetCamera() { return m_Camera; }
	inline const Scope<EntityManager>& GetEntityManager() { return m_EM; }
	inline const Scope<TileManager>& GetTileManager() { return m_TM; }

	inline static const Ref<GameCamera>& GetSceneCamera() { return s_Instance->GetCamera(); }
	inline static const Scope<EntityManager>& GetSceneMarioEntityManager() { return s_Instance->GetEntityManager(); }
	inline static const Scope<TileManager>& GetSceneTileManager() { return s_Instance->GetTileManager(); }

	void LoadMap(std::filesystem::path path);

private:
	static GameLayer* s_Instance;

private:
	Ref<GameCamera> m_Camera;

	Scope<EntityManager> m_EM;
	Scope<TileManager> m_TM;
};