#pragma once

#include "Crystal/Core/Core.hpp"

#include <vector>

#include <glm/glm.hpp>

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
		virtual std::string GetProjectRelativePath() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void SetData(const std::vector<glm::vec4>& data) = 0;
		virtual void UpdateSubTexture(int x, int y, int width, int height) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		enum class ManipMode
		{
			None = -1, Read, Write, ReadWrite
		};
		virtual void BindToImageUnit(uint32_t unit = 0, ManipMode mode = ManipMode::ReadWrite) const = 0;
		virtual void UnBindFromImageUnit(uint32_t unit = 0, ManipMode mode = ManipMode::ReadWrite) const = 0;
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