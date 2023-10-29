#include "ECSLayer.hpp"

ECSLayer::ECSLayer()
{
}

ECSLayer::~ECSLayer()
{
}

void ECSLayer::OnAttach()
{
	//m_Project = CreateRef<Project>("New");
	Window& window = Application::Get().GetWindow();

	m_Camera = CreateRef<Camera2D>(window.GetViewportWidth(), window.GetViewportHeight());
	//m_Camera->SetOrigin({ -window.GetViewportWidth() / 2.0f, window.GetViewportHeight() / 2.0f });
	m_Camera->SetMovementSpeed(1000.0f);

	//ECS::Entity entity = ECS::Entity::Create(m_Project->GetStorage(), "NameEntityOrSomething");
	//entity.AddComponent<ECS::TagComponent>(ECS::TagComponent("Mario"));

	//ECS::TransformComponent tc;
	//tc.Position = { 1.0f, 0.0f, 20.0f };
	//tc.Size = { 10.0f, 9.0f, 0.0f };
	//tc.Rotation = 0.0f;

	//entity.AddComponent<ECS::TransformComponent>(tc);

	//ECS::Renderer2DComponent r2d;
	//r2d.Colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	//entity.AddComponent<ECS::Renderer2DComponent>(r2d);

	//m_Project->AddEntity(entity);
	KeyPressedEvent e(CR_KEY_R, 0); 
	Reload(e); //TODO(Jorben): Remove stupid KeyPressedEvent
}

void ECSLayer::OnDetach()
{
}

void ECSLayer::OnUpdate(Timestep& ts)
{
	m_Camera->OnUpdate(ts);
}

void ECSLayer::OnRender()
{
	RendererCommand::Clear();

	for (ECS::Entity& entity : m_Project->GetEntities())
	{
		ECS::Renderer2DComponent* r2d = entity.GetComponent<ECS::Renderer2DComponent>();
		if (r2d) // TODO(Jorben): Editor Camera
		{
			ECS::TransformComponent* transform = entity.GetComponent<ECS::TransformComponent>();

			if (r2d->Texture) 
				Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Texture, false, m_Camera->GetCamera());
			else
				Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Colour, false, m_Camera->GetCamera());
		}
	}
}

void ECSLayer::OnImGuiRender()
{
}

void ECSLayer::OnEvent(Event& e)
{
	EventHandler handler(e);

	handler.Handle<KeyPressedEvent>(CR_BIND_EVENT_FN(ECSLayer::Reload));
	handler.Handle<MouseButtonPressedEvent>(CR_BIND_EVENT_FN(ECSLayer::MousePress));

	m_Camera->OnEvent(e);
}

bool ECSLayer::Reload(KeyPressedEvent& e)
{
	if (e.GetKeyCode() == CR_KEY_R)
	{
		m_Project = CreateRef<Project>("New");

		ProjectSerializer serializer(m_Project);
		//serializer.Serialize("test.crproj");
		serializer.Deserialize("test.crproj");

		for (auto& entity : m_Project->GetEntities())
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
			// TODO(Jorben): Renderer2DComponent
		}
	}

	return false;
}

bool ECSLayer::MousePress(MouseButtonPressedEvent& e)
{

	return false;
}
