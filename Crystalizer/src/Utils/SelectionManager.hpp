#pragma once

#include <Crystal/Crystal.hpp>

namespace Crystal
{

	class SelectionManager
	{
	public:
		SelectionManager();
		virtual ~SelectionManager();

		void OnUpdate(Timestep& ts);
		void OnRender();
		void OnEvent(Event& e);
		
		void ResetSelected() { m_Selected = nullptr; }
		void SetSelected(Ref<ECS::Entity> entity) { m_Selected = entity; }
		Ref<ECS::Entity> GetSelected() const { return m_Selected; }

		static SelectionManager* Get() { return s_Instance; }

	private:
		enum class SelectionState
		{
			None = 0, Transform, Scale, Rotation
		};

		enum class Direction
		{
			None = 0, X, Y, Z
		};

		bool ButtonPress(MouseButtonPressedEvent& e);
		void HandleSelection();
		void HandleArrows();

		void DrawSelectedSquare(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, SelectionState state = SelectionState::Transform);

	private:
		static SelectionManager* s_Instance;

		Ref<ECS::Entity> m_Selected = nullptr;
		
		SelectionState m_State;
		Direction m_Direction;
	};

}