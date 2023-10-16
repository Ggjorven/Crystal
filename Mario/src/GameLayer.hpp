#pragma once

#include <Crystal/Crystal.hpp>
#include <Crystal/Examples/Camera2D.hpp>

#include "Game/Managers.hpp"

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

	inline const Ref<Camera2D> GetCamera() { return m_Camera; }
	inline static const Ref<Camera2D> GetSceneCamera() { return s_Instance->GetCamera(); }

private:
	static GameLayer* s_Instance;

private:
	Ref<Camera2D> m_Camera;

	Scope<EntityManager> m_EM;
	Scope<TileManager> m_TM;
};