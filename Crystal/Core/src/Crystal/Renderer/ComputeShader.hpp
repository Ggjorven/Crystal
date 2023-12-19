#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

#include "Crystal/Renderer/Renderer.hpp"
#include "Crystal/Renderer/RenderingAPI.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <filesystem>

namespace Crystal
{

	template<typename Input, typename Output>
	class ComputeShader
	{
	public:
		ComputeShader() = default;
		virtual ~ComputeShader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetInputBuffer(void* data, size_t size) = 0;
		virtual void SetInputBuffer(const std::vector<Input>& input) = 0;
		virtual void UpdateInputBuffer(const std::vector<Input>& input) = 0;
		virtual void UpdateInputBuffer(void* data, size_t size) = 0;
		virtual void CreateOutputBuffer(size_t resultSize) = 0;

		virtual void SetUniformInt1(const std::string& name, int value) = 0;
		virtual void SetUniformFloat(const std::string& name, float value) = 0;
		virtual void SetUniformFloat2(const std::string& name, const Vec2<float>& value) = 0;
		virtual void SetUniformFloat3(const std::string& name, const Vec3<float>& value) = 0;
		virtual void SetUniformFloat4(const std::string& name, const Vec4<float>& value) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual void SetGroupSize(int32_t x, int32_t y, int32_t z) = 0;

		virtual void Dispatch(int32_t groupsX, int32_t groupsY, int32_t groupsZ, size_t outputSize) = 0;

		virtual std::vector<Output> GetResults() = 0;
	};

}