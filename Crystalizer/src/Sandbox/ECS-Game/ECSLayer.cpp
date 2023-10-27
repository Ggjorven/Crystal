#include "ECSLayer.hpp"

ECSLayer::ECSLayer()
{
}

ECSLayer::~ECSLayer()
{
}

void ECSLayer::OnAttach()
{
	m_Scene = CreateRef<Scene>("Patat");

	ECS::Entity entity = ECS::Entity::Create(m_Scene->GetStorage(), "NameEntityOrSomething");
	entity.AddComponent<ECS::TagComponent>(ECS::TagComponent("Mario"));

	ECS::TransformComponent tc;
	tc.Position = { 1.0f, 0.0f, 20.0f };
	tc.Size = { 10.0f, 9.0f, 0.0f };
	tc.Rotation = 0.0f;

	entity.AddComponent<ECS::TransformComponent>(tc);

	m_Scene->AddEntity(entity);

	SceneSerializer serializer(m_Scene);
	serializer.Serialize("test.crproj");
	//serializer.Deserialize("test.yaml");

	for (auto& entity : m_Scene->GetEntities())
	{
		CR_WARN("Entity ({0}) info:", entity.GetUUID());
		
		if (entity.GetComponent<ECS::TagComponent>())
			CR_WARN("\tTag: {0}", entity.GetComponent<ECS::TagComponent>()->Tag);

		if (entity.GetComponent<ECS::TransformComponent>())
		{
			ECS::TransformComponent& transformComponent = *entity.GetComponent<ECS::TransformComponent>();
			CR_WARN("\tTransforms:");
			CR_WARN("\t\tPosition [{0}, {1}, {2}]", transformComponent.Position.x, transformComponent.Position.y, transformComponent.Position.z);
			CR_WARN("\t\tSize [{0}, {1}, {2}]", transformComponent.Size.x, transformComponent.Size.y, transformComponent.Size.z);
			CR_WARN("\t\tRotation: {0}", transformComponent.Rotation);
		}
	}
}

void ECSLayer::OnDetach()
{
}

void ECSLayer::OnUpdate(Timestep& ts)
{
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

	return false;
}
