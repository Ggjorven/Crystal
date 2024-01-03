#include "CustomLayer.hpp"

#include <GL/glew.h>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

CustomLayer::CustomLayer(const ApplicationInfo& appinfo)
{
}

CustomLayer::~CustomLayer()
{
}

void CustomLayer::OnAttach()
{
}

void CustomLayer::OnDetach()
{
}

void CustomLayer::OnUpdate(Timestep& ts)
{
}

void CustomLayer::OnRender()
{
	RendererCommand::Clear();
	RendererCommand::EnableDepth(false);

	BatchRenderer2D::BeginBatch();

	BatchRenderer2D::Quad quad;
	quad.Position = { 0.0f, 0.0f };
	quad.Size = { 1.0f, 1.0f };
	quad.Colour = { 0.8f, 0.5f, 0.3f, 1.0f };

	BatchRenderer2D::AddQuad(quad);

	BatchRenderer2D::EndBatch();

	BatchRenderer2D::Flush();

	//Renderer2D::DrawQuad(quad.Position, quad.Size, quad.Colour);
}

void CustomLayer::OnImGuiRender()
{
}

void CustomLayer::OnEvent(Event& e)
{
}
