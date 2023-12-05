#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

namespace Crystal
{

	class AABBCollider
	{
	public:
		AABBCollider();
		virtual ~AABBCollider();

		Vec3<float>& GetSize() { return m_Size; }
		void SetSize(const Vec3<float>& size) { m_Size = size; }

		Vec3<float>& GetPosition() { return m_Position; }
		void SetPosition(const Vec3<float>& position) { m_Position = position; }

		bool& LinkedPosition() { return m_PosLinked; }
		bool& LinkedSize() { return m_SizeLinked; }

		void SetPostionLinked(bool enabled) { m_PosLinked = enabled; }
		void SetSizeLinked(bool enabled) { m_SizeLinked = enabled; }

	private:
		Vec3<float> m_Position = { 0.0f, 0.0f, 0.0f };
		bool m_PosLinked = false;

		Vec3<float> m_Size = { 0.0f, 0.0f, 0.0f };
		bool m_SizeLinked = false;
	};
}