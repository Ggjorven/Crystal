#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

#include <glm/glm.hpp>

namespace Crystal
{

	class OrthoGraphicCamera
	{
	public:
		OrthoGraphicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const Vec3<float>& position) { m_Position = position; CalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }

		const Vec3<float>& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void CalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		Vec3<float> m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}