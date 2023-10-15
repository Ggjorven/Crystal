#include "crpch.h"
#include "Buffer.hpp"

#include "Crystal/Renderer/Renderer.hpp"
#include "APIs/OpenGL/OpenGLBuffer.hpp" //vertex & index

namespace Crystal
{

	uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		CR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	std::string ShaderDataTypeToString(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return "Float";
		case ShaderDataType::Float2:   return "Float2";
		case ShaderDataType::Float3:   return "Float3";
		case ShaderDataType::Float4:   return "Float3";
		case ShaderDataType::Mat3:     return "Mat3";
		case ShaderDataType::Mat4:     return "Mat4";
		case ShaderDataType::Int:      return "Int";
		case ShaderDataType::Int2:     return "Int2";
		case ShaderDataType::Int3:     return "Int3";
		case ShaderDataType::Int4:     return "Int4";
		case ShaderDataType::Bool:     return "Bool";
		}

		CR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return "";
	}

	std::string BufferElement::ToString()
	{
		std::stringstream ss;
		ss << "Name: " << Name << ", Type: " << ShaderDataTypeToString(Type) << ", Size: " << Size << ", Offset: " << Offset << ", Normalized: " << Normalized;
		
		return ss.str();
	}

	std::string BufferLayout::ToString()
	{
		std::stringstream ss;

		for (int i = 0; i < m_Elements.size(); i++)
			ss << m_Elements[i].ToString() << std::endl;

		return ss.str();
	}

	BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
	{
	}

	uint32_t BufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3 * 3;
		case ShaderDataType::Mat4:    return 4 * 4;
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}

		CR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		size_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None:    CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None:    CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}
}