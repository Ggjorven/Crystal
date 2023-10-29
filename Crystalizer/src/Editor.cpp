#include "Editor.hpp"

EditorLayer::EditorLayer(const ApplicationInfo& appinfo)
	: m_Panels(nullptr)
{
	Window& window = Application::Get().GetWindow();
	window.SetVSync(true);

	m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);

	m_Project = CreateRef<Project>("New");
	m_Panels = CreateRef<Panels>(m_Project);
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnAttach()
{
	ProjectSerializer serializer(m_Project);

	serializer.Deserialize(m_Path);
}

void EditorLayer::OnDetach()
{
	ProjectSerializer serializer(m_Project);

	serializer.Serialize(m_Path);
}

void EditorLayer::OnUpdate(Timestep& ts)
{
}

void EditorLayer::OnRender()
{
	m_FrameBuffer->Bind();

	RendererCommand::Clear();

	for (ECS::Entity& entity : m_Project->GetEntities())
	{
		ECS::Renderer2DComponent* r2d = entity.GetComponent<ECS::Renderer2DComponent>();
		if (r2d) // TODO(Jorben): Editor Camera
		{
			ECS::TransformComponent* transform = entity.GetComponent<ECS::TransformComponent>();

			if (r2d->Texture && r2d->UseTexture)
				Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Texture, false);
			else
				Renderer2D::DrawQuad(glm::vec2(transform->Position.x, transform->Position.y), glm::vec2(transform->Size.x, transform->Size.y), r2d->Colour, false);
		}
	}

	m_FrameBuffer->Unbind();
}

void EditorLayer::OnImGuiRender()
{
	ImGui::DockSpaceOverViewport();

	//Menu bar
	{
		Panels::BeginColours();
		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New project"))
			{
				m_Project.reset();
				m_Project = CreateRef<Project>("New");
				ProjectSerializer serializer(m_Project);

				serializer.Serialize("New-Project.crproj");
			}

			if (ImGui::MenuItem("Open project"))
			{
				std::string file = Utils::OpenFile("");

				if (!file.empty())
				{
					m_Project.reset();
					m_Project = CreateRef<Project>("New");

					ProjectSerializer serializer(m_Project);
					m_Path = file;
					serializer.Deserialize(m_Path);
				}

			}

			if (ImGui::MenuItem("Save project"))
			{
				ProjectSerializer serializer(m_Project);

				serializer.Serialize(m_Path);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
		Panels::EndColours();
	}

	//Viewport
	{	
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); //NECESSARY FOR RESIZING FRAMEBUFFER
		ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_None);

		ImVec2 size = ImGui::GetContentRegionAvail();
		if (size.x != 0 && size.y != 0) //Check if window is collapsed
			m_FrameBuffer->Resize((uint32_t)size.x, (uint32_t)size.y);

		ImGui::Image((void*)m_FrameBuffer->GetColorAttachmentRendererID(), size, { 0, 1 }, { 1, 0 });

		//Update viewport size
		Window& window = Application::Get().GetWindow();

		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
		ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

		window.SetViewportWidth(ImGui::GetWindowSize().x);
		window.SetViewportHeight(ImGui::GetWindowSize().y);
		window.SetViewportX(relativePos.x);
		window.SetViewportY(relativePos.y);

		ImGui::End();
		ImGui::PopStyleVar(1);
	}

	//Objects window
	m_Panels->ObjectsWindow();
	m_Panels->ObjectPropertiesWindow();
}

void EditorLayer::OnEvent(Event& e)
{

}

bool EditorLayer::InWindow(ImVec2 windowPos, ImVec2 windowSize, MousePosition mousePosition)
{
	if (mousePosition.X >= windowPos.x && mousePosition.X <= windowSize.x + windowPos.x &&
		mousePosition.Y >= windowPos.y && mousePosition.Y <= windowSize.y + windowPos.y)
		return true;

	return false;
}
