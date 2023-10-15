#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Crystal
{

	struct ShaderSource
	{
	public:
		std::string VertexSource;
		std::string FragmentSource;

		ShaderSource() = default;
		ShaderSource(const std::string& vertexSource, const std::string& fragmentSource)
			: VertexSource(vertexSource), FragmentSource(fragmentSource)
		{
		}
	};

	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetUniformInt1(const std::string& name, int value) = 0;
		virtual void SetUniformFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() = 0;

		static ShaderSource Read(const std::string& filepath);

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

	private:

	};

	class ShaderLib
	{
	public:
		enum class Type
		{
			None = 0,

			Coloured, Textured, Textured_Coloured,
			Coloured_Transform, Textured_Transform, Textured_Coloured_Transform,
			Coloured_Transform_ViewProj, Textured_Transform_ViewProj, Textured_Coloured_Transform_ViewProj, Textured_Coloured_Transform_ViewProj_TexCoord
		};

	public:
		ShaderLib() = default;			//Only to be used by the engine not the client
		virtual ~ShaderLib() = default;

		inline static ShaderSource GetShaderSource(ShaderLib::Type type) { return s_Instance->GetShaderSourceImplementation(type); }

		static Scope<ShaderLib> Create();

	protected:
		virtual ShaderSource GetShaderSourceImplementation(ShaderLib::Type type) = 0;

	private:
		static Scope<ShaderLib> s_Instance;
	};

}