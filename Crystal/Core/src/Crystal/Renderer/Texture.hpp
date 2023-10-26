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
		virtual uint32_t GetFormat() const = 0;

		virtual uint32_t GetRendererID() const = 0;
		virtual const std::string& GetPath() const = 0;

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

	/*
	* In pixel space
	*/
	struct TexCoords
	{
	public:
		int32_t X, Y;
		int32_t Width, Height;

	public:
		TexCoords(int32_t x = 0, int32_t y = 0, int32_t width = 0, int32_t height = 0)
			: X(x), Y(y), Width(width), Height(height)
		{
		}
	};

}