#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Events.hpp"
#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Core/Events/Codes/KeyCodes.hpp"

#include "Crystal/Renderer/2D/OrthoGraphicCamera.hpp"
#include "Crystal/Renderer/3D/PerspectiveCamera.hpp"

#include <glm/glm.hpp>

namespace Crystal
{

	class EditorCamera2D
	{
	public:
		EditorCamera2D();
		virtual ~EditorCamera2D();

		void OnUpdate(Timestep& ts);
		void OnEvent(Event& e);

		Ref<OrthoGraphicCamera>& GetCamera() { return m_Camera; }
		glm::vec2 GetPosition() const { return m_Position; }
		float GetZoom() const { return m_Zoom; }

		void SetMovementKey(int key) { m_MovementKey = key; }
		//void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }

	private:
		bool MousePress(MouseButtonPressedEvent& e);
		bool MouseScrolled(MouseScrolledEvent& e);

	private:
		Ref<OrthoGraphicCamera> m_Camera;

		int m_MovementKey = CR_KEY_LEFT_ALT;
		glm::vec2 m_DefaultPosition = { 0.0f, 0.0f };
		glm::vec2 m_Position = { 0.0f, 0.0f };
		float m_Zoom = 1.0f;
		//float m_MovementSpeed = 400.0f
		MousePosition m_LastMousePosition;
	};

	class EditorCamera3D
	{
	public:
		EditorCamera3D();
		virtual ~EditorCamera3D();

		void OnUpdate(Timestep& ts);
		void OnEvent(Event& e);

		inline Ref<PerspectiveCamera>& GetCamera() { return m_Camera; }

	private:
		bool MousePressedEvent(MouseButtonPressedEvent& e);
		bool KeyEvent(KeyPressedEvent& e);

	private:
		Ref<PerspectiveCamera> m_Camera;
		MousePosition m_LastMousePosition;
		bool m_FirstUpdate = true;

		float m_MovementSpeed;
		float m_MouseSensitivity;
	};

}