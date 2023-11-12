#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

namespace Crystal::UI
{

	bool BeginECSComponent(const char* label);
	void Vector3(const char* label, Vec3<float>& value, const Vec4<float>& colourX, const Vec4<float>& colourY, const Vec4<float>& colourZ);

}