#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

namespace Crystal
{

	template<typename T>
	struct Vec2
	{
	public:
		union {
			struct { T X, Y; };
			struct { T x, y; };
			struct { T R, G; };
			struct { T r, g; };
			T data[2];
		};

	public:
		Vec2(T x, T y)
			: X(x), Y(y)
		{
		}
		Vec2(const glm::vec2& vec)
			: X(vec.x), Y(vec.y)
		{
		}

		Vec2(T* arr)
			: X(arr[0]), Y(arr[1])
		{
		}

		T* GetData()
		{
			return &X;
		}

		operator glm::vec2() const
		{
			return glm::vec2(X, Y);
		}

		Vec2 operator+(const Vec2& vec) const 
		{
			return Vec2(X + vec.X, Y + vec.Y);
		}

		Vec2 operator-(const Vec2& vec) const 
		{
			return Vec2(X - vec.X, Y - vec.Y);
		}

		Vec2 operator*(const Vec2& vec) const 
		{
			return Vec2(X * vec.X, Y * vec.Y);
		}

		Vec2 operator/(const Vec2& vec) const 
		{
			if (vec.X == 0 || vec.Y == 0) 
			{
				CR_CORE_WARN("Tried to divide by 0, returned original Vector");
				return Vec2(X, Y);
			}
			return Vec2(X / vec.X, Y / vec.Y);
		}

		Vec2& operator+=(const Vec2& vec) 
		{
			X += vec.X;
			Y += vec.Y;
			return *this;
		}

		Vec2& operator-=(const Vec2& vec) 
		{
			X -= vec.X;
			Y -= vec.Y;
			return *this;
		}

		Vec2& operator*=(const Vec2& vec) 
		{
			X *= vec.X;
			Y *= vec.Y;
			return *this;
		}

		Vec2& operator/=(const Vec2& vec) 
		{
			if (vec.X == 0 || vec.Y == 0)
			{
				CR_CORE_WARN("Tried to divide by 0, returned original Vector");
				return Vec2(X, Y);
			}
			X /= vec.X;
			Y /= vec.Y;
			return *this;
		}
	};

	template<typename T>
	struct Vec3
	{
	public:
		union {
			struct { T X, Y, Z; };
			struct { T x, y, z; };
			struct { T R, G, B; };
			struct { T r, g, b; };
			//struct { T x, X, r, R; };
			//struct { T y, Y, g, G; };
			//struct { T z, Z, b, B; };
			T data[3];
		};

	public:
		Vec3(T x, T y, T z)
			: X(x), Y(y), Z(z)
		{
		}
		Vec3(const glm::vec3& vec)
			: X(vec.x), Y(vec.y), Z(vec.z)
		{
		}

		Vec3(T* arr)
			: X(arr[0]), Y(arr[1]), Z(arr[2])
		{
		}

		T* GetData()
		{
			return &X;
		}

		operator glm::vec3() const
		{
			return glm::vec3(X, Y, Z);
		}

		Vec3 operator+(const Vec3& vec) const 
		{
			return Vec3(X + vec.X, Y + vec.Y, Z + vec.Z);
		}

		Vec3 operator-(const Vec3& vec) const 
		{
			return Vec3(X - vec.X, Y - vec.Y, Z - vec.Z);
		}

		Vec3 operator*(const Vec3& vec) const 
		{
			return Vec3(X * vec.X, Y * vec.Y, Z * vec.Z);
		}

		Vec3 operator/(const Vec3& vec) const 
		{
			if (vec.X == 0 || vec.Y == 0 || vec.Z == 0) 
			{
				CR_CORE_WARN("Tried to divide by 0, returned original Vector");
				return Vec3(X, Y, Z);
			}
			return Vec3(X / vec.X, Y / vec.Y, Z / vec.Z);
		}

		Vec3& operator+=(const Vec3& vec) 
		{
			X += vec.X;
			Y += vec.Y;
			Z += vec.Z;
			return *this;
		}

		Vec3& operator-=(const Vec3& vec) 
		{
			X -= vec.X;
			Y -= vec.Y;
			Z -= vec.Z;
			return *this;
		}

		Vec3& operator*=(const Vec3& vec) 
		{
			X *= vec.X;
			Y *= vec.Y;
			Z *= vec.Z;
			return *this;
		}

		Vec3& operator/=(const Vec3& vec) 
		{
			if (vec.X == 0 || vec.Y == 0 || vec.Z == 0)
			{
				CR_CORE_WARN("Tried to divide by 0, returned original Vector");
				return Vec3(X, Y, Z);
			}
			X /= vec.X;
			Y /= vec.Y;
			Z /= vec.Z;
			return *this;
		}
	};

	template<typename T>
	struct Vec4
	{
	public:
		union {
			struct { T X, Y, Z, W; };
			struct { T x, y, z, w; };
			struct { T R, G, B, A; };
			struct { T r, g, b, a; };
			T data[4];
		};

	public:
		Vec4(T x, T y, T z, T w)
			: X(x), Y(y), Z(z), W(w)
		{
		}
		Vec4(const glm::vec4& vec)
			: X(vec.x), Y(vec.y), Z(vec.z), W(vec.w)
		{
		}

		Vec4(T* arr)
			: X(arr[0]), Y(arr[1]), Z(arr[2]), W(arr[3])
		{
		}

		T* GetData()
		{
			return &X;
		}

		operator glm::vec4() const 
		{
			return glm::vec4(X, Y, Z, W);
		}

		Vec4 operator+(const Vec4& vec) const 
		{
			return Vec4(X + vec.X, Y + vec.Y, Z + vec.Z, W + vec.W);
		}

		Vec4 operator-(const Vec4& vec) const 
		{
			return Vec4(X - vec.X, Y - vec.Y, Z - vec.Z, W - vec.W);
		}

		Vec4 operator*(const Vec4& vec) const 
		{
			return Vec4(X * vec.X, Y * vec.Y, Z * vec.Z, W * vec.W);
		}

		Vec4 operator/(const Vec4& vec) const 
		{
			if (vec.X == 0 || vec.Y == 0 || vec.Z == 0 || vec.W == 0) 
			{
				CR_CORE_WARN("Tried to divide by 0, returned original Vector");
				return Vec4(X, Y, Z, W);
			}
			return Vec4(X / vec.X, Y / vec.Y, Z / vec.Z, W / vec.W);
		}

		Vec4& operator+=(const Vec4& vec) 
		{
			X += vec.X;
			Y += vec.Y;
			Z += vec.Z;
			W += vec.W;
			return *this;
		}

		Vec4& operator-=(const Vec4& vec) 
		{
			X -= vec.X;
			Y -= vec.Y;
			Z -= vec.Z;
			W -= vec.W;
			return *this;
		}

		Vec4& operator*=(const Vec4& vec) 
		{
			X *= vec.X;
			Y *= vec.Y;
			Z *= vec.Z;
			W *= vec.W;
			return *this;
		}

		Vec4& operator/=(const Vec4& vec) 
		{
			if (vec.X == 0 || vec.Y == 0 || vec.Z == 0 || vec.W == 0)
			{
				CR_CORE_WARN("Tried to divide by 0, returned original Vector");
				return Vec4(X, Y, Z, W);
			}
			X /= vec.X;
			Y /= vec.Y;
			Z /= vec.Z;
			W /= vec.W;
			return *this;
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
