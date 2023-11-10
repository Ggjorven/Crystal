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

		static void OnDrawCall();

		//Rendering functions
		//
		//Coloured
		static void DrawCube(const Vec3<float>& position, const Vec3<float>& size, const Vec4<float>& colour, bool reversed = false, const Ref<PerspectiveCamera>& camera = nullptr);
		static void DrawCube(const Vec3<float>& position, const Vec3<float>& size, const Vec3<float>& origin, const Vec4<float>& colour, bool reversed = false, const Ref<PerspectiveCamera>& camera = nullptr);
	};

}