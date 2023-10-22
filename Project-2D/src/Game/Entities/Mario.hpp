#pragma once

#include "Game/Entities/Entity.hpp"

class Mario : public MarioEntity
{
public:
	Mario(const std::string_view& debugName, const glm::vec2& position, const glm::vec2& size);
	virtual ~Mario();

	void OnUpdate(Timestep& ts) override;
	void OnRender() override;
	void OnImGuiRender() override;

	void OnEvent(Event& e) override;


private:
	enum class State
	{
		None = 0, Crouching, Running, Jumping, Dead
	};

private:
	Timestep m_CoordChangeInterval;
	Timestep m_CurrentTimer;

private:
	State m_State;
};