#include "crpch.h"
#include "Project.hpp"

#include "Crystal/Renderer/2D/Renderer2D.hpp"

namespace Crystal
{

	Project* Project::s_CurrentProject = nullptr;

	Project::Project(const std::string& debugName)
		: m_DebugName(debugName)
	{
		m_EditorCamera = CreateRef<EditorCamera>();
		s_CurrentProject = this;
	}

	Project::~Project() = default;

	void Project::OnUpdate(Timestep& ts)
	{
		// TODO(Jorben): Add logic for if in editor or if not
		m_EditorCamera->OnUpdate(ts);
	}

	void Project::OnRenderRuntime()
	{
		/*
		for (ECS::Entity& entity : m_Entities)
		{
			ECS::Renderer2DComponent* r2d = entity.GetComponent<ECS::Renderer2DComponent>();
			ECS::TransformComponent* transform = entity.GetComponent<ECS::TransformComponent>();
			if (r2d && r2d->Enable && transform)
			{
				if (r2d->Texture && r2d->UseTexture)
					Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Texture, false, m_EditorCamera->GetCamera());
				else
					Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Colour, false, m_EditorCamera->GetCamera());
			}
		}
		*/
	}

	void Project::OnRenderEditor()
	{
		for (ECS::Entity& entity : m_Entities)
		{
			ECS::Renderer2DComponent* r2d = entity.GetComponent<ECS::Renderer2DComponent>();
			ECS::TransformComponent* transform = entity.GetComponent<ECS::TransformComponent>();
			if (r2d && r2d->Enable && transform)
			{
				if (r2d->Texture && r2d->UseTexture)
					Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Texture, false, m_EditorCamera->GetCamera());
				else
					Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Colour, false, m_EditorCamera->GetCamera());
			}
		}
	}

	void Project::OnEvent(Event& e)
	{
		m_EditorCamera->OnEvent(e);
	}

}