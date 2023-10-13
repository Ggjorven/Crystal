#include "crpch.h"
#include "OpenGLShader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Crystal
{

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string fragmentSource)
		: m_Name(name), m_RendererID(0)
	{
		m_RendererID = Create(vertexSource, fragmentSource);
		//EX_CORE_WARN("OpenGLShader m_RendererID: {0}", m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
		//EX_CORE_WARN("OpenGLShader bound.");
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt1(const std::string& name, int value)
	{
		//TODO uniform setting

		GLint location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
	{
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		//Bind();

		GLint location = GetUniformLocation(name);
		glUniform4f(location, value.r, value.g, value.b, value.a); //GL_INVALID_OPERATION without Bind()?
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = GetUniformLocation(name);
		//glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	GLuint OpenGLShader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		GLuint program = glCreateProgram();

		GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
		GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glValidateProgram(program);

		//Check for linking failure
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetProgramInfoLog(program, length, &length, &infoLog[0]);

			glDeleteProgram(program);

			CR_CORE_ERROR("{0}", infoLog.data());
			CR_CORE_ASSERT(false, "Shader link failure!");
			return 0;
		}

		//Cleanup
		glDeleteShader(m_IntermediateShaderIDs[GL_VERTEX_SHADER]);
		glDeleteShader(m_IntermediateShaderIDs[GL_FRAGMENT_SHADER]);

		return program;
	}

	GLuint OpenGLShader::Compile(GLenum type, const std::string& data)
	{
		GLuint id = glCreateShader(type);

		const char* source = data.c_str();
		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);


		//Check for compilation failure
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(id, length, &length, &infoLog[0]);

			glDeleteShader(id);
			return 0;
		}

		m_IntermediateShaderIDs[type] = id;
		return id;
	}

	GLint OpenGLShader::GetUniformLocation(const std::string& name)
	{
		Bind(); //So you don't have to explicitly do it yourself

		//TODO cache
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1)
			CR_CORE_ASSERT(false, "Uniform does not exist.", name); //Shader probably not bound

		return location;
	}

	//===============================
	//--------Shader Source----------
	//===============================
	// 
	//--------------------------
	//		   Defaults
	//--------------------------
	static ShaderSource Colour = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;

		void main()
		{
			gl_Position = vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 colour;

		uniform vec4 u_Colour;

		void main()
		{
			colour = u_Colour;
		}
	)"
	};

	static ShaderSource Texture = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 colour;

		in vec2 v_TexCoord;

		uniform sampler2D u_Texture;

		void main()
		{
			colour = texture(u_Texture, v_TexCoord);
		}
	)"
	};
	static ShaderSource TextureColour = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 colour;

		in vec2 v_TexCoord;

		uniform vec4 u_Colour;
		uniform sampler2D u_Texture;

		void main()
		{
			colour = texture(u_Texture, v_TexCoord) * u_Color;
		}
	)"
	};

	//--------------------------
	//		   Transforms
	//--------------------------
	static ShaderSource ColourT = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_Transform;

		void main()
		{
			gl_Position = u_Transform * vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		uniform vec4 u_Colour;

		void main()
		{
			colour = u_Colour;
		}
	)"
	};

	static ShaderSource TextureT = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		uniform mat4 u_Transform;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = u_Transform * vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 colour;

		in vec2 v_TexCoord;

		uniform sampler2D u_Texture;

		void main()
		{
			colour = texture(u_Texture, v_TexCoord);
		}
	)"
	};

	static ShaderSource TextureColourT = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		uniform mat4 u_Transform;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = u_Transform * vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 colour;

		in vec2 v_TexCoord;

		uniform vec4 u_Colour;
		uniform sampler2D u_Texture;

		void main()
		{
			colour = texture(u_Texture, v_TexCoord) * u_Colour ;
		}
	)"
	};

	//--------------------------
	//		ViewProjections
	//--------------------------
	static ShaderSource ColourTVP = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_Transform;
		uniform mat4 u_ViewProj;

		void main()
		{
			gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		uniform vec4 u_Colour;

		void main()
		{
			colour = u_Colour;
		}
	)"
	};

	static ShaderSource TextureTVP = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		uniform mat4 u_Transform;
		uniform mat4 u_ViewProj;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 colour;

		in vec2 v_TexCoord;

		uniform sampler2D u_Texture;

		void main()
		{
			colour = texture(u_Texture, v_TexCoord);
		}
	)"
	};
	static ShaderSource TextureColourTVP = {
		R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		uniform mat4 u_Transform;
		uniform mat4 u_ViewProj;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
		}
	)",
		R"(
		#version 330 core

		layout(location = 0) out vec4 colour;

		in vec2 v_TexCoord;

		uniform vec4 u_Colour;
		uniform sampler2D u_Texture;

		void main()
		{
			colour = texture(u_Texture, v_TexCoord) * u_Colour ;
		}
	)"
	};

	/*
		--Things might want to add to the shaders--

		out vec2 v_ScreenPos;
		v_ScreenPos = gl_Position.xy;
		in vec2 v_ScreenPos;

		//float dist = 1.0f - distance(v_ScreenPos * 0.8f, vec2(0.0f));
		//dist = clamp(dist, 0.0f, 1.0f);
		//dist = sqrt(dist);
	*/
	
	ShaderSource OpenGLShaderLib::GetShaderSourceImplementation(ShaderLib::Type type)
	{
		switch (type)
		{
		case ShaderLib::Type::Coloured: return Colour;
		case ShaderLib::Type::Textured: return Texture;
		case ShaderLib::Type::Textured_Coloured: return TextureColour;

		case ShaderLib::Type::Coloured_Transform: return ColourT;
		case ShaderLib::Type::Textured_Transform: return TextureT;
		case ShaderLib::Type::Textured_Coloured_Transform: return TextureColourT;

		case ShaderLib::Type::Coloured_Transform_ViewProj: return ColourTVP;
		case ShaderLib::Type::Textured_Transform_ViewProj: return TextureTVP;
		case ShaderLib::Type::Textured_Coloured_Transform_ViewProj: return TextureColourTVP;
		}

		CR_CORE_ASSERT(false, "Not a proper shader selected.");
		return ShaderSource("error", "error");
	}
}