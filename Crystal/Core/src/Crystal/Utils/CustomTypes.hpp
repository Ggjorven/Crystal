#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

namespace Crystal
{

	// Vectors
	template<typename T>
	struct Vec2
	{
	public:
		T X, Y;
		T* ValuePtr;

	public:
		Vec2(T x, T y)
			: X(x), Y(y)
		{
		}
		Vec2(const glm::vec2& vec)
			: X(vec.x), Y(vec.y), ValuePtr(&X)
		{
		}
	};

	template<typename T>
	struct Vec3
	{
	public:
		T X, Y, Z;
		T* ValuePtr;

	public:
		Vec3(T x, T y, T z)
			: X(x), Y(y), Z(z)
		{
		}
		Vec3(const glm::vec3& vec)
			: X(vec.x), Y(vec.y), Z(vec.z), ValuePtr(&X)
		{
		}
	};

	template<typename T>
	struct Vec4
	{
	public:
		T X, Y, Z, W;
		T* ValuePtr;

	public:
		Vec4(T x, T y, T z, T w)
			: X(x), Y(y), Z(z), W(w)
		{
		}
		Vec4(const glm::vec4& vec)
			: X(vec.x), Y(vec.y), Z(vec.z), W(vec.w), ValuePtr(&X)
		{
		}
	};

	//Transform them to glm::vec's
	template<typename Type>
	glm::vec2 Convert(Vec2<Type> vec)
	{
		return glm::vec2(vec.X, vec.Y);
	}

	template<typename Type>
	glm::vec3 Convert(Vec3<Type> vec)
	{
		return glm::vec3(vec.X, vec.Y, vec.Z);
	}

	template<typename Type>
	glm::vec4 Convert(Vec4<Type> vec)
	{
		return glm::vec4(vec.X, vec.Y, vec.Z, vec.W);
	}

}