#include "Editor.hpp"

#include <string>

EditorLayer::EditorLayer(const ApplicationInfo& appInfo)
{
	Window& window = Application::Get().GetWindow();
	window.SetVSync(true);

	m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);

	m_Project = CreateRef<Project>("New");
	m_Panels = CreateRef<Panels>(m_Project);

	if (appInfo.ArgCount > 1)
		m_Path = std::filesystem::path(appInfo.Args[0]).parent_path() / std::filesystem::path(appInfo.Args[1]);
}

EditorLayer::~EditorLayer() = default;

void EditorLayer::OnAttach()
{
	if (!m_Path.empty())
	{
		ProjectSerializer serializer(m_Project);
		serializer.Deserialize(m_Path);
	}
	//Wrapper::Component::TagComponent_GetTag(m_Project->GetEntities()[0].GetUUID());
	//Wrapper::Component::TagComponent_SetTag(m_Project->GetEntities()[0].GetUUID(), Coral::NativeString("ABC"));
}

void EditorLayer::OnDetach()
{
	ProjectSerializer serializer(m_Project);
	serializer.Serialize(m_Path);
}

void EditorLayer::OnUpdate(Timestep& ts)
{
	m_Project->OnUpdate(ts);
}

void EditorLayer::OnRender()
{
	m_FrameBuffer->Bind();
	RendererCommand::Clear();

	if (!m_Running)
	{
		m_Project->OnRenderEditor();
	}
	else
	{
		m_Project->OnRenderRuntime();
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
				CreateNewProject();
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
		Panels::BeginColours();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); // Note(Jorben): Necessary for resizing framebuffer
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

		window.SetViewportWidth((uint32_t)ImGui::GetWindowSize().x);
		window.SetViewportHeight((uint32_t)ImGui::GetWindowSize().y);
		window.SetViewportX((uint32_t)relativePos.x);
		window.SetViewportY((uint32_t)relativePos.y);

		ImGui::End();
		ImGui::PopStyleVar(1);
		Panels::EndColours();
	}

	//Windows
	m_Panels->ObjectsWindow();
	m_Panels->ObjectPropertiesWindow();
	m_Panels->RunWindow(m_Running);

	// TODO(Jorben): Add dockspace information for ImGui somehow, to prevent having to copy imgui.ini files
	/*
	[Window][DockSpaceViewport_11111111]
	Pos=0,19
	Size=1920,998
	Collapsed=0

	[Window][Debug##Default]
	Pos=60,60
	Size=400,400
	Collapsed=0

	[Window][Viewport]
	Pos=274,19
	Size=1646,998
	Collapsed=0
	DockId=0x00000002,0

	[Window][Properties]
	Pos=0,580
	Size=272,437
	Collapsed=0
	DockId=0x00000004,0

	[Window][Objects]
	Pos=0,19
	Size=272,559
	Collapsed=0
	DockId=0x00000003,0

	[Docking][Data]
	DockSpace     ID=0x8B93E3BD Window=0xA787BDB4 Pos=0,42 Size=1920,998 Split=X
	DockNode    ID=0x00000001 Parent=0x8B93E3BD SizeRef=272,998 Split=Y Selected=0x967E7699
	DockNode  ID=0x00000003 Parent=0x00000001 SizeRef=272,559 Selected=0x967E7699
	DockNode  ID=0x00000004 Parent=0x00000001 SizeRef=272,437 Selected=0x199AB496
	DockNode    ID=0x00000002 Parent=0x8B93E3BD SizeRef=1646,998 CentralNode=1 Selected=0x13926F0B
	*/
}

void EditorLayer::OnEvent(Event& e)
{
	m_Project->OnEvent(e);
}

bool EditorLayer::InWindow(ImVec2 windowPos, ImVec2 windowSize, MousePosition mousePosition)
{
	if (mousePosition.X >= windowPos.x && mousePosition.X <= windowSize.x + windowPos.x &&
		mousePosition.Y >= windowPos.y && mousePosition.Y <= windowSize.y + windowPos.y)
		return true;

	return false;
}

void EditorLayer::CreateNewProject()
{
	//Save
	ProjectSerializer serializer(m_Project);

	serializer.Serialize(m_Path);

	//New
	m_Project.reset();
	m_Project = CreateRef<Project>("New");
	m_Path = "New-Project-" + std::to_string(UUIDGenerator::GenerateUUID()) + ".crproj"; //New path

	serializer = ProjectSerializer(m_Project);

	serializer.Serialize(m_Path);
}
