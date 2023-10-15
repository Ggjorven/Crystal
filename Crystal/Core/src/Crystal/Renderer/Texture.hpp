#pragma once

#include "Crystal/Core/Core.hpp"

namespace Crystal
{
	
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual unsigned char* GetData() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void UpdateSubTexture(int x, int y, int width, int height) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};

	struct TexCoords
	{
	public:
		uint32_t X, Y;
		uint32_t Width, Height;

	public:
		TexCoords(uint32_t x = 0u, uint32_t y = 0u, uint32_t width = 0u, uint32_t height = 0u)
			: X(x), Y(y), Width(width), Height(height)
		{
		}
	};

}