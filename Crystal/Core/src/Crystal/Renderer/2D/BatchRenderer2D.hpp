#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Renderer/2D/OrthoGraphicCamera.hpp"

namespace Crystal
{

	class BatchRenderer2D
	{
	public:
		static void Init();
		static void Shutdown() { s_Instance->ShutdownImplementation(); }

		static void BeginBatch() { s_Instance->BeginBatchImplementation(); }
		static void EndBatch() { s_Instance->EndBatchImplementation(); }

		static void Flush() { s_Instance->FlushBatchImplementation(); }

		// TODO(Jorben): Add more functionality
		struct Quad
		{
		public:
			glm::vec2 Position = { 0.0f, 0.0f };
			glm::vec2 Size = { 0.0f, 0.0f };

			glm::vec4 Colour = { 0.0f, 0.0f, 0.0f, 0.0f };

		public:
			Quad() = default;
			Quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour)
				: Position(position), Size(size), Colour(colour) { }
		};

		struct QuadVertexData
		{
		public:
			glm::vec2 Position = { 0.0f, 0.0f };

			glm::vec4 Colour = { 0.0f, 0.0f, 0.0f, 0.0f };

		public:
			QuadVertexData() = default;
			QuadVertexData(const glm::vec2& position, const glm::vec4& colour)
				: Position(position), Colour(colour) { }
		};

		static void AddQuad(const BatchRenderer2D::Quad& quad) { s_Instance->AddQuadImplementation(quad); }

	private:
		virtual void InitImplementation() = 0;
		virtual void ShutdownImplementation() = 0;

		virtual void BeginBatchImplementation() = 0;
		virtual void EndBatchImplementation() = 0;

		virtual void FlushBatchImplementation() = 0;

		virtual void AddQuadImplementation(const BatchRenderer2D::Quad& quad) = 0;

	protected:
		uint32_t m_MaxQuads = 1000u;

	private:
		static BatchRenderer2D* s_Instance;
	};

}