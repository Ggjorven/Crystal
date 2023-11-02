#include "RuntimeLayer.hpp"

namespace Crystal
{

	RuntimeLayer::RuntimeLayer()
		: Layer("Runtime")
	{
		m_Project = CreateRef<Project>("");
	}

	RuntimeLayer::~RuntimeLayer()
	{
	}

	void RuntimeLayer::OnAttach()
	{
		ProjectSerializer serializer(m_Project);

		serializer.Deserialize(m_Path);
	}

	void RuntimeLayer::OnDetach()
	{
	}

	void RuntimeLayer::OnUpdate(Timestep& ts)
	{
	}

	void RuntimeLayer::OnRender()
	{
		RendererCommand::Clear();

		for (ECS::Entity& entity : m_Project->GetEntities())
		{
			ECS::Renderer2DComponent* r2d = entity.GetComponent<ECS::Renderer2DComponent>();
			ECS::TransformComponent* transform = entity.GetComponent<ECS::TransformComponent>();
			if (r2d && transform) // TODO(Jorben): Runtime Camera or something
			{
				if (r2d->Texture && r2d->Enable && r2d->UseTexture)
					Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Texture, false);
				else
					Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Colour, false);
			}
		}
	}

	void RuntimeLayer::OnImGuiRender()
	{
	}

	void RuntimeLayer::OnEvent(Event& e)
	{
	}

}