#pragma once

#include "Crystal/Core/Core.hpp"

#include <GL/glew.h>

#include "Crystal/Renderer/Shader.hpp"

#include <unordered_map>

namespace Crystal
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::filesystem::path path);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string fragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;

		void SetUniformInt1(const std::string& name, int value) override;
		void SetUniformFloat(const std::string& name, float value) override;
		void SetUniformFloat2(const std::string& name, const Vec2<float>& value) override;
		void SetUniformFloat3(const std::string& name, const Vec3<float>& value) override;
		void SetUniformFloat4(const std::string& name, const Vec4<float>& value) override;
		void SetUniformMat4(const std::string& name, const glm::mat4& value) override;

		const std::string& GetName() override { return m_Name; }

	private:
		GLuint Create(const std::string& vertexSource, const std::string& fragmentSource);
		GLuint Compile(GLenum type, const std::string& data);

		GLint GetUniformLocation(const std::string& name);

	private:
		uint32_t m_RendererID;
		std::string m_Name;

		std::unordered_map<GLenum, GLint> m_IntermediateShaderIDs;
		std::unordered_map<std::string, GLint> m_UniformCache; //TODO
	};

	class OpenGLShaderLib : public ShaderLib
	{
	public:
		OpenGLShaderLib() = default;
		virtual ~OpenGLShaderLib() = default;

		ShaderSource GetShaderSourceImplementation(ShaderLib::Type type) override;
	};

}