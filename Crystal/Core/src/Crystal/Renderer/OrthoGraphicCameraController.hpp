#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Events/ApplicationEvent.hpp"
#include "Crystal/Events/Event.hpp"
#include "Crystal/Events/KeyEvent.hpp"
#include "Crystal/Events/MouseEvent.hpp"

#include "Crystal/Renderer/OrthoGraphicCamera.hpp"

namespace Crystal
{

	class OrthoGraphicCameraController
	{
	public:
		OrthoGraphicCameraController(float width, float height, bool rotation = false);

		void OnUpdate(Timestep& ts);
		void OnEvent(Event& e);

		Ref<OrthoGraphicCamera>& GetCamera() { return m_Camera; }
		const Ref<OrthoGraphicCamera>& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_Width;
		float m_Height;

		float m_ZoomLevel = 1.0f;
		Ref<OrthoGraphicCamera> m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}