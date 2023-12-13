#include "crpch.h"
#include "OpenGLTexture.hpp"

#include "Crystal/Data/Project/Project.hpp"

#include <stb_image.h>

namespace Crystal
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_RendererID(0), m_Width(width), m_Height(height), m_Data(nullptr)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_RendererID(0), m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		m_Data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		// Note(Jorben): When this issue arises make sure CRYSTAL_DIR is set.
		CR_CORE_ASSERT(m_Data, "Failed to load image: {0}", path);
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		CR_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_Data);
	
		//glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		stbi_image_free((void*)m_Data);
		glDeleteTextures(1, &m_RendererID);
	}

	std::string OpenGLTexture2D::GetProjectRelativePath() const
	{
		std::filesystem::path projDir = Project::GetCurrentProject()->GetProjectDir();
		std::filesystem::path assetDir = Project::GetCurrentProject()->GetAssetDir();

		std::filesystem::path relPath = std::filesystem::relative(std::filesystem::path(m_Path), projDir / assetDir);

		return relPath.string();
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		CR_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		//glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLTexture2D::UpdateSubTexture(int x, int y, int width, int height)
	{
		// TODO: maybe?
		CR_CORE_ASSERT(false, "NOT SUPPORTED");
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}