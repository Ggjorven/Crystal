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
		// TODO(Jorben): Add runtime camera
		if (m_State == State::Editor)
		{
			m_EditorCamera->OnUpdate(ts);
			m_FirstUpdate = true;
		}

		else if (m_State == State::Runtime)
		{
			for (Ref<ECS::Entity>& entity : m_Entities)
			{
				if (Ref<ECS::ScriptComponent> sc = entity->GetComponent<ECS::ScriptComponent>())
				{
					if (m_FirstUpdate)
					{
						sc->Script->UpdateValueFieldsValues();
						sc->Script->OnCreate();
						m_FirstUpdate = false;
					}
					sc->Script->OnUpdate(ts);
				}
			}
			m_EditorCamera->OnUpdate(ts); // TODO(Jorben): Remove and replace with runtime camera
		}
	}

	void Project::OnRender()
	{
		if (m_State == State::Editor)
			OnRenderEditor();
		if (m_State == State::Runtime)
			OnRenderRuntime();
	}

	void Project::OnEvent(Event& e)
	{
		if (m_State == State::Editor)
			m_EditorCamera->OnEvent(e);
		else if (m_State == State::Runtime)
			m_EditorCamera->OnEvent(e); // TODO(Jorben): Replace editorcamera with runtime camera
	}

	Ref<ECS::Entity> Project::GetEntityByUUID(uint64_t uuid)
	{
		for (Ref<ECS::Entity>& entity : m_Entities)
		{
			if (entity->GetUUID() == uuid)
				return entity;
		}
		CR_CORE_WARN("No entity with UUID ({0}) found in current project...", uuid);
		return nullptr;
	}

	void Project::OnRenderRuntime()
	{
		// TODO(Jorben): Add runtime camera
		for (Ref<ECS::Entity> entity : m_Entities)
		{
			Ref<ECS::Renderer2DComponent> r2d = entity->GetComponent<ECS::Renderer2DComponent>();
			Ref<ECS::TransformComponent> transform = entity->GetComponent<ECS::TransformComponent>();
			if (r2d && r2d->Enable && transform)
			{
				if (r2d->Texture && r2d->UseTexture)
					Renderer2D::DrawQuad(Vec2<float>(transform->Position.x, transform->Position.y), Vec2<float>(transform->Size.x, transform->Size.y), Vec2<float>(transform->Size.x / 2.0f, transform->Size.y / 2.0f * -1), r2d->Texture, false, m_EditorCamera->GetCamera());
				else
					Renderer2D::DrawQuad(Vec2<float>(transform->Position.x, transform->Position.y), Vec2<float>(transform->Size.x, transform->Size.y), Vec2<float>(transform->Size.x / 2.0f, transform->Size.y / 2.0f * -1), r2d->Colour, false, m_EditorCamera->GetCamera());
			}
		}

	}

	void Project::OnRenderEditor()
	{
		for (Ref<ECS::Entity> entity : m_Entities)
		{
			Ref<ECS::Renderer2DComponent> r2d = entity->GetComponent<ECS::Renderer2DComponent>();
			Ref<ECS::TransformComponent> transform = entity->GetComponent<ECS::TransformComponent>();
			if (r2d && r2d->Enable && transform)
			{
				if (r2d->Texture && r2d->UseTexture)
					Renderer2D::DrawQuad(Vec2<float>(transform->Position.x, transform->Position.y), Vec2<float>(transform->Size.x, transform->Size.y), Vec2<float>(transform->Size.x / 2.0f, transform->Size.y / 2.0f * -1), r2d->Texture, false, m_EditorCamera->GetCamera());
				else
					Renderer2D::DrawQuad(Vec2<float>(transform->Position.x, transform->Position.y), Vec2<float>(transform->Size.x, transform->Size.y), Vec2<float>(transform->Size.x / 2.0f, transform->Size.y / 2.0f * -1), r2d->Colour, false, m_EditorCamera->GetCamera());
			}
		}
	}

}