#include "crpch.h"
#include "Shader.hpp"

#include "Crystal/Renderer/Renderer.hpp"

#include "APIs/OpenGL/OpenGLShader.hpp"

namespace Crystal
{
	Scope<ShaderLib> ShaderLib::s_Instance = ShaderLib::Create();


	ShaderSource Shader::Read(const std::string& filepath)
	{
		enum class ShaderType
		{
			None = -1, Vertex = 0, Fragment = 1
		};

		ShaderSource source;
		ShaderType type = ShaderType::None;

		std::ifstream file(filepath);
		std::string line;
		std::stringstream ss[2];

		while (getline(file, line))
		{

			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::Vertex; continue;
				}
				if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::Fragment; continue;
				}
			}

			ss[(int)type] << line << "\n";
		}

		source.VertexSource = ss[(int)ShaderType::Vertex].str();
		source.FragmentSource = ss[(int)ShaderType::Fragment].str();

		return source;
	}



	Ref<Shader> Shader::Create(std::filesystem::path path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: CreateScope<OpenGLShader>(path);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateScope<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

	Scope<ShaderLib> ShaderLib::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateScope<OpenGLShaderLib>();
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

}