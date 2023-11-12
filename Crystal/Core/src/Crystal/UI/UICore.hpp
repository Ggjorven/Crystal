#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

#include "Crystal/Renderer/Texture.hpp"

namespace Crystal::UI
{

	bool BeginECSComponent(const char* label, Ref<Texture2D> icon = nullptr);
	void Vector3(const char* label, Vec3<float>& value, const Vec4<float>& colourX, const Vec4<float>& colourY, const Vec4<float>& colourZ);

}