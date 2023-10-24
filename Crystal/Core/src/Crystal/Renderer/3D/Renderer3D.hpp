#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Renderer/3D/PerspectiveCamera.hpp"

namespace Crystal
{

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		//Rendering functions
		//
		//Coloured
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& colour, bool reversed = false, const Ref<PerspectiveCamera>& camera = nullptr);
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& origin, const glm::vec4& colour, bool reversed = false, const Ref<PerspectiveCamera>& camera = nullptr);
	};

}