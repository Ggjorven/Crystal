#pragma once

#include "Crystal/Core/Core.hpp"

#include <GL/glew.h>

#include "Crystal/Renderer/ComputeShader.hpp"

#include <unordered_map>

namespace Crystal
{

	template<typename Input, typename Output>
	class OpenGLComputeShader : public ComputeShader<Input, Output>
	{
	public:
		OpenGLComputeShader(std::filesystem::path path)
		{
			// TODO(Jorben): Add this function
			// ...
		}
		OpenGLComputeShader(const std::string& source)
		{
			CompileShader(source.c_str());
		}

		~OpenGLComputeShader()
		{
			glDeleteProgram(m_ComputeProgram);
			glDeleteShader(m_ComputeShader);
			DeleteInputBuffer();
			DeleteOutputBuffer();
		}

		void Bind() const override { glUseProgram(m_ComputeProgram); }
		void UnBind() const override { glUseProgram(0); }

		void SetInputBuffer(const std::vector<Input>& input) override
		{
			DeleteInputBuffer();
			CreateInputBuffer(input.size() * sizeof(Input), input.data(), GL_DYNAMIC_COPY);

			m_InputData = input;
		}

		void UpdateInputBuffer(const std::vector<Input>& input) override
		{
			if (!m_InputBuffer)
			{
				CR_CORE_ERROR("Input buffer not initialized. Call SetInputBuffer first.");
				return;
			}

			CreateInputBuffer(input.size() * sizeof(Input), input.data(), GL_DYNAMIC_COPY);

			m_InputData = input;
		}

		void CreateOutputBuffer(size_t resultSize) override
		{
			DeleteOutputBuffer();
			Bind();
			// Create a buffer for the output data
			glGenBuffers(1, &m_OutputBuffer);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_OutputBuffer);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Output) * resultSize, nullptr, GL_DYNAMIC_DRAW);
		}

		void SetGroupSize(int32_t x, int32_t y, int32_t z) override
		{
			m_WorkgroupSizeX = x;
			m_WorkgroupSizeY = y;
			m_WorkgroupSizeZ = z;
		}

		void Dispatch(int32_t groupsX, int32_t groupsY, int32_t groupsZ, size_t outputSize) override
		{
			Input* data_ptr = (Input*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, sizeof(Input) * m_InputData.size(),
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
			std::copy(m_InputData.begin(), m_InputData.end(), data_ptr);
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

			// Bind the input buffer to a specific binding point if needed
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_InputBuffer);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_OutputBuffer);

			glDispatchCompute(groupsX * m_WorkgroupSizeX, groupsY * m_WorkgroupSizeY, groupsZ * m_WorkgroupSizeZ);

			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

			// Map the output data buffer and read the result
			Output* result_ptr = (Output*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

			// Copy the result to m_OutputData
			m_OutputData.resize(outputSize / sizeof(Output));
			std::copy(result_ptr, result_ptr + (outputSize / sizeof(Output)), m_OutputData.begin());

			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		}


		std::vector<Output> GetResults() override
		{
			return m_OutputData;
		}

	private:
		void CompileShader(const char* source)
		{
			m_ComputeShader = glCreateShader(GL_COMPUTE_SHADER);
			glShaderSource(m_ComputeShader, 1, &source, nullptr);
			glCompileShader(m_ComputeShader);

			CheckShaderCompileStatus(m_ComputeShader);

			m_ComputeProgram = glCreateProgram();
			glAttachShader(m_ComputeProgram, m_ComputeShader);
			glLinkProgram(m_ComputeProgram);

			CheckProgramLinkStatus(m_ComputeProgram);

			glUseProgram(m_ComputeProgram);
		}

		void CheckShaderCompileStatus(GLuint shader) const
		{
			GLint success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				CR_CORE_ERROR("Error compiling compute shader:\n{0}", infoLog);
			}
		}

		void CheckProgramLinkStatus(GLuint program) const
		{
			GLint success;
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetProgramInfoLog(program, 512, nullptr, infoLog);
				CR_CORE_ERROR("Error linking compute program:\n{0}", infoLog);
			}
		}

		void CreateInputBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage)
		{
			Bind();

			glGenBuffers(1, &m_InputBuffer);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_InputBuffer);
			glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);

			// Correct binding point for input buffer
			//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_InputBuffer);
			//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}

		void DeleteInputBuffer()
		{
			glDeleteBuffers(1, &m_InputBuffer);
			m_InputBuffer = 0;
		}

		void DeleteOutputBuffer()
		{
			glDeleteBuffers(1, &m_OutputBuffer);
			m_OutputBuffer = 0;
		}

	private:
		uint32_t m_ComputeShader = 0;
		uint32_t m_ComputeProgram = 0;

		std::vector<Input> m_InputData = { };
		uint32_t m_InputBuffer = 0u;
		std::vector<Output> m_OutputData = { };
		uint32_t m_OutputBuffer = 0u;

		int32_t m_WorkgroupSizeX = 1;
		int32_t m_WorkgroupSizeY = 1;
		int32_t m_WorkgroupSizeZ = 1;
	};

}