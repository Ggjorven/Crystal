#include "ECSLayer.hpp"

ECSLayer::ECSLayer()
{
}

ECSLayer::~ECSLayer()
{
}

void ECSLayer::OnAttach()
{
	m_Entity = ECS::Entity::Create(m_Storage, "ABC-Entity");

	m_Entity->AddComponent<ECS::TransformComponent>();
}

void ECSLayer::OnDetach()
{
}

void ECSLayer::OnUpdate(Timestep& ts)
{
	ECS::TransformComponent& transform = m_Entity->GetComponent<ECS::TransformComponent>();
	//CR_TRACE("Transform: X: {0}, Y: {1}, Z: {2}", transform.Position.x, transform.Position.y, transform.Position.z);
}

void ECSLayer::OnRender()
{
}

void ECSLayer::OnImGuiRender()
{
}

void ECSLayer::OnEvent(Event& e)
{
	EventHandler handler(e);

	handler.Handle<MouseButtonPressedEvent>(CR_BIND_EVENT_FN(ECSLayer::MousePress));
}

bool ECSLayer::MousePress(MouseButtonPressedEvent& e)
{
	ECS::TransformComponent& transform = m_Entity->GetComponent<ECS::TransformComponent>();

	transform.Position.x += 1;

	return false;
}
