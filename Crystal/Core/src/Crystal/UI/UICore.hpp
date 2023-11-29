#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

#include "Crystal/Renderer/Texture.hpp"

namespace Crystal::UI
{

	struct ComponentOptions
	{
	public:
		bool Remove = false;

	public:
		ComponentOptions() = default;
	};

	void Init();

	bool BeginECSComponent(const char* label, ComponentOptions& componentOptions, Ref<Texture2D> icon = nullptr);
	void Vector3(const char* label, Vec3<float>& value, const Vec4<float>& colourX, const Vec4<float>& colourY, const Vec4<float>& colourZ);

	// TODO(Jorben): A centered popup for example for project settings

	static Ref<Texture2D> s_ECSComponentDropdown = nullptr;

}