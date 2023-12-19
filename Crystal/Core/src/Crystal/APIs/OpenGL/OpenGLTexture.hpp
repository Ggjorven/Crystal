#pragma once 

#include "Crystal/Core/Core.hpp"

#include "Crystal/Renderer/Texture.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Crystal
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual unsigned char* GetData() const override { return m_Data; }
		virtual uint32_t GetFormat() const override { return m_DataFormat; }

		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		virtual const std::string& GetPath() const override { return m_Path; }
		virtual std::string GetProjectRelativePath() const override;

		virtual void SetData(void* data, uint32_t size) override;
		virtual void SetData(const std::vector<glm::vec4>& data) override;
		virtual void UpdateSubTexture(int x, int y, int width, int height) override;

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;

		GLenum m_InternalFormat, m_DataFormat;
		unsigned char* m_Data;
	};

}