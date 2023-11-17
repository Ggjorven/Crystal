#include "Editor.hpp"

#include "Crystal/Utils/CustomTypes.hpp"

#include <imgui_internal.h>

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
	
	Ref<ECS::TransformComponent> tc = m_Project->GetStorage().GetComponent<ECS::TransformComponent>(11900670760340589512);
	if (tc != nullptr)
	{
		CR_CORE_TRACE("{0} {1} {2}", tc->Position.X, tc->Position.Y, tc->Position.Z);
	}
	
	const char* settings =
		R"(
[Window][DockSpaceViewport_11111111]
Pos=0,19
Size=1280,701
Collapsed=0

[Window][Debug##Default]
Pos=60,60
Size=400,400
Collapsed=0

[Window][Viewport]
Pos=333,19
Size=947,701
Collapsed=0
DockId=0x00000002,0

[Window][Objects]
Pos=0,19
Size=331,372
Collapsed=0
DockId=0x00000003,0

[Window][Properties]
Pos=0,393
Size=331,327
Collapsed=0
DockId=0x00000004,0

[Docking][Data]
DockSpace     ID=0x8B93E3BD Window=0xA787BDB4 Pos=216,258 Size=1280,701 Split=X
  DockNode    ID=0x00000001 Parent=0x8B93E3BD SizeRef=331,701 Split=Y Selected=0x967E7699
    DockNode  ID=0x00000003 Parent=0x00000001 SizeRef=223,372 Selected=0x967E7699
    DockNode  ID=0x00000004 Parent=0x00000001 SizeRef=223,327 HiddenTabBar=1 Selected=0x199AB496
  DockNode    ID=0x00000002 Parent=0x8B93E3BD SizeRef=947,701 CentralNode=1 HiddenTabBar=1 Selected=0x13926F0B

	)";

	ImGuiIO& io = ImGui::GetIO();
	io.WantSaveIniSettings = true;

	ImGui::ClearIniSettings();
	ImGui::LoadIniSettingsFromMemory(settings, std::strlen(settings));

	settings = ImGui::SaveIniSettingsToMemory();
	io.WantSaveIniSettings = false;
	
}

void EditorLayer::OnDetach()
{
	ProjectSerializer serializer(m_Project);
	serializer.Serialize(m_Path);
}

void EditorLayer::OnUpdate(Timestep& ts)
{
	m_Project->OnUpdate(ts);
	m_Project->SetState((m_Running ? Project::State::Runtime : Project::State::Editor));
}

void EditorLayer::OnRender()
{
	m_FrameBuffer->Bind();
	RendererCommand::Clear();

	m_Project->OnRender();

	m_FrameBuffer->Unbind();
}

void EditorLayer::OnImGuiRender()
{
	ImGui::DockSpaceOverViewport();

	MenuBar();

	//Windows
	ViewPort();
	m_Panels->ObjectsWindow();
	m_Panels->ObjectPropertiesWindow();
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
	std::string random = std::to_string(UUIDGenerator::GenerateUUID());
	m_Path = Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\Projects\\New-Project-" + random + "New-Project-" + random + ".crproj"; //New path

	serializer = ProjectSerializer(m_Project);
	serializer.Serialize(m_Path);
}

void EditorLayer::MenuBar()
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
				m_Path = file;

				m_Project.reset();
				m_Project = CreateRef<Project>("New");

				ProjectSerializer serializer(m_Project);
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

void EditorLayer::ViewPort()
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

	Vec2<float> buttonSize(24.f, 24.f);

	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2.0f - buttonSize.x, 6.0f));

	if (ImGui::ImageButton((ImTextureID)Panels::s_ButtonTex->GetRendererID(), ImVec2(buttonSize.x, buttonSize.y), { 0, 1 }, { 1, 0 }))
	{
		// TODO(Jorben): Add a better system for resetting the project
		/*
		ProjectSerializer serializer(m_Project);
		if (m_Running)
		{
			m_Project.reset();
			m_Project = CreateRef<Project>();
			serializer.Deserialize(m_Path);
		}
		else
		{
			serializer.Serialize(m_Path);
		}
		*/

		m_Running = !m_Running;
		Panels::SwitchButtons();
	}

	ImGui::End();
	ImGui::PopStyleVar(1);
	Panels::EndColours();
}
