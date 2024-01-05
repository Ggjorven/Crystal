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

	BatchRenderer2D::Quad quad1;
	quad1.Position = { 0.5f, 0.0f };
	quad1.Size = { 0.8f, 0.8f };
	quad1.Colour = { 0.8f, 0.5f, 0.3f, 1.0f };

	BatchRenderer2D::Quad quad2;
	quad2.Position = { -0.5f, -0.5f };
	quad2.Size = { 0.5f, 0.5f };
	quad2.Colour = { 0.4f, 1.0f, 0.0f, 1.0f };

	BatchRenderer2D::AddQuad(quad1);
	BatchRenderer2D::AddQuad(quad2);

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
