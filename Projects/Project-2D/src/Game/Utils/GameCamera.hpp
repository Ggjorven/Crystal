#pragma once

#include <Crystal/Core/Core.hpp>

#include <glm/glm.hpp>

#include <Crystal/Core/Events/Events.hpp>

#include <Crystal/Renderer/2D/OrthoGraphicCamera.hpp>

using namespace Crystal;

class GameCamera
{
public:
	GameCamera(float width, float height, bool rotation = false);
	virtual ~GameCamera();

	void Init();

	void OnUpdate(Timestep& ts);
	void OnEvent(Event& e);

	Ref<OrthoGraphicCamera>& GetCamera() { return m_Camera; }
	const Ref<OrthoGraphicCamera>& GetCamera() const { return m_Camera; }

	float GetZoomLevel() const { return m_ZoomLevel; }
	void SetZoomLevel(float level) { m_ZoomLevel = level; }

	float GetMovementSpeed() { return m_MovementSpeed; }
	void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }

	float GetRotationSpeed() { return m_RotationSpeed; }
	void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }

	float GetMaxZoomLevel() { return m_MaxZoomLevel; }
	void SetMaxZoomLevel(float max) { m_MaxZoomLevel = max; }

	void SetPosition(glm::vec2 position) { m_CameraPosition = { position.x, position.y, 0.0f }; UpdateView(); }
	glm::vec3& GetPosition() { return m_CameraPosition; }

	void Move(glm::vec2 position) { m_CameraPosition.x += position.x; m_CameraPosition.y += position.y; UpdateView(); }

private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);

	void UpdateView();
	void SetPositionToLowestTile();

private:
	float m_Width;
	float m_Height;

	uint32_t m_LastScale;

	float m_ZoomLevel = 1.0f;
	Ref<OrthoGraphicCamera> m_Camera;

	bool m_Rotation;

	glm::vec2 m_Origin = { 0.0f, 0.0f };
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f; //In degrees, in the clockwise direction

	float m_MovementSpeed = 5.0f, m_RotationSpeed = 180.0f;
	float m_MaxZoomLevel = 0.25f;
};