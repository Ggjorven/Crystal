#include "SelectionManager.hpp"

#include "Panels/Panels.hpp"

namespace Crystal
{

	SelectionManager* SelectionManager::s_Instance = nullptr;

	SelectionManager::SelectionManager()
	{
		s_Instance = this;
	}

	SelectionManager::~SelectionManager()
	{
		s_Instance = nullptr;
	}

	void SelectionManager::OnUpdate(Timestep& ts)
	{
		if (!m_Selected) return;
		// TODO(Jorben): Add dragging logic

	}

	void SelectionManager::OnRender()
	{
		if (!m_Selected) return;

		if (m_Selected->HasComponent<ECS::TransformComponent>())
		{
			ECS::TransformComponent& transform = m_Selected->GetComponent<ECS::TransformComponent>();

			DrawSelectedSquare(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), SelectionState::Transform);
		}
	}

	void SelectionManager::OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<MouseButtonPressedEvent>(CR_BIND_EVENT_FN(SelectionManager::ButtonPress));
	}

	bool SelectionManager::ButtonPress(MouseButtonPressedEvent& e) // TODO(Jorben): Fix zoom
	{
		if (e.GetMouseButton() == CR_MOUSE_BUTTON_LEFT)
		{
			Ref<ECS::Entity> e = m_Selected;
			HandleSelection();
			
			// If not changed (aka. selected a new entity)
			if (e == m_Selected)
				HandleArrows();
		}

		return false;
	}

	void SelectionManager::HandleSelection()
	{
		// Get viewport position and size
		float viewportX = (float)Application::Get().GetWindow().GetViewportX();
		float viewportY = (float)Application::Get().GetWindow().GetViewportY();
		float viewportHeight = (float)Application::Get().GetWindow().GetViewportHeight();

		// Get camera position and zoom
		auto cameraPosition = Project::GetCurrentProject()->GetCurrentScene()->GetEditorCamera()->GetPosition();
		float zoom = Project::GetCurrentProject()->GetCurrentScene()->GetEditorCamera()->GetZoom();

		// Get mouse position and adjust it relative to the viewport
		MousePosition rawPosition = Input::GetMousePosition();

		// Convert mouse position to world coordinates with zoom factor
		MousePosition worldPosition;
		worldPosition.X = (((rawPosition.X - viewportX)) + cameraPosition.x);
		worldPosition.Y = (((viewportHeight - (rawPosition.Y - viewportY))) + cameraPosition.y);

		ECS::Storage& storage = Project::GetCurrentProject()->GetCurrentScene()->GetStorage();
		for (auto& t : storage.GetComponentsMap<ECS::TransformComponent>())
		{
			ECS::TransformComponent& transform = storage.GetComponent<ECS::TransformComponent>(t.first);

			// Apply zoom to entity position and size
			Vec2<float> bottomLeft = Vec2<float>(transform.Position.x, transform.Position.y);
			Vec2<float> topRight = bottomLeft + Vec2<float>(transform.Size.x, transform.Size.y);

			if (worldPosition.X >= bottomLeft.x && worldPosition.X <= topRight.x &&
				worldPosition.Y >= bottomLeft.y && worldPosition.Y <= topRight.y)
			{
				m_Selected = Project::GetCurrentProject()->GetCurrentScene()->GetEntityByUUID(t.first);
				Panels::Get()->SetSelectedEntity(Project::GetCurrentProject()->GetCurrentScene()->GetEntityByUUID(t.first));
				break;
			}
		}
	}

	void SelectionManager::HandleArrows()
	{
	}

	void SelectionManager::DrawSelectedSquare(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, SelectionState state)
	{
		constexpr const float Size = 4.f;

		Ref<OrthoGraphicCamera>& camera = Project::GetCurrentProject()->GetCurrentScene()->GetEditorCamera()->GetCamera();

		// Left
		Renderer2D::DrawQuad(Vec2<float>(position.x - Size, position.y - Size), Vec2<float>(Size, size.y + (Size * 2.0f)), Vec2<float>(Size / 2.0f, ( size.y + (Size * 2.0f)) / 2.0f), Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), false, camera);

		// Right
		Renderer2D::DrawQuad(Vec2<float>(position.x + size.x, position.y - Size), Vec2<float>(Size, size.y + (Size * 2.0f)), Vec2<float>(Size / 2.0f, (size.y + (Size * 2.0f)) / 2.0f), Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), false, camera);

		// Top
		Renderer2D::DrawQuad(Vec2<float>(position.x - Size, position.y + size.Y), Vec2<float>(size.x + (Size * 2.0f), Size), Vec2<float>((size.x + (Size * 2.0f)) / 2.0f, Size / 2.0f), Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), false, camera);

		// Bottom
		Renderer2D::DrawQuad(Vec2<float>(position.x - Size, position.y - Size), Vec2<float>(size.x + (Size * 2.0f), Size), Vec2<float>((size.x + (Size * 2.0f)) / 2.0f, Size / 2.0f), Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), false, camera);


		//Arrows

	}

}