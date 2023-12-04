#include "Editor.hpp"

#include "Crystal/Utils/CustomTypes.hpp"

#include <imgui_internal.h>

#include <string>
#include <fstream>

EditorLayer::EditorLayer(const ApplicationInfo& appInfo)
{
	Window& window = Application::Get().GetWindow();
	window.SetVSync(true);

	m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);

	m_Project = CreateRef<Project>("New");
	// TEMP // TODO(Jorben): Remove
	//m_Project->AddScene("D:\\Code\\C++\\VS\\Crystal\\Crystalizer\\Projects\\TestProj\\Scenes\\test.crscene");
	//SaveProject();

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
	
	const char* settings = R"(
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
	
	UI::Init();
}

void EditorLayer::OnDetach()
{
	//SaveProject();
}

void EditorLayer::OnUpdate(Timestep& ts)
{
	m_Project->SetState((m_Running ? Project::State::Runtime : Project::State::Editor));
	m_Project->OnUpdate(ts);
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
	// TODO(Jorben): Add Assets/Scenes/etc browser

	//ImGui::ShowStyleEditor();
}

void EditorLayer::OnEvent(Event& e)
{
	EventHandler handler(e);

	handler.Handle<KeyPressedEvent>(CR_BIND_EVENT_FN(EditorLayer::KeyEvent));
	handler.Handle<WindowCloseEvent>(CR_BIND_EVENT_FN(EditorLayer::WindowClose));
	
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
	SaveProject();

	std::string path = Utils::SaveFile(".crproj\0*.crproj\0All Files\0*.*\0", Project::GetCurrentProject()->GetProjectDir().parent_path().string().c_str());
	if (!path.empty())
	{
		//New
		m_Project.reset();
		m_Project = CreateRef<Project>("New");

		std::ofstream outFile(path);
		outFile << " " << std::endl;

		m_Path = std::filesystem::path(path);

		ProjectSerializer serializer(m_Project);
		serializer.Serialize(m_Path);


		serializer.Deserialize(m_Path);
	}
}

void EditorLayer::SaveProject()
{
	if (m_Running)
	{
		m_Project->GetCurrentScene()->ResetStorage();

		m_Running = false;
		Panels::SwitchButtons();
	}

	ProjectSerializer serializer(m_Project);
	serializer.Serialize(m_Path);

	m_Project->SaveScene();
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
			std::string file = Utils::OpenFile(".crproj\0*.crproj\0All Files\0*.*\0", Project::GetCurrentProject()->GetProjectDir().parent_path().string().c_str());

			if (!file.empty())
			{
				m_Path = file;

				m_Project.reset();
				m_Project = CreateRef<Project>("New");

				ProjectSerializer serializer(m_Project);
				serializer.Deserialize(m_Path);
			}
		}

		if (ImGui::MenuItem("Save project", "Ctrl+S"))
		{
			SaveProject();
		}
		ImGui::EndMenu();
	}

	ImGui::Dummy(ImVec2(3.f, 0.0f));

	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Add C# assembly"))
		{
			std::string file = Utils::OpenFile(".dll\0*.dll", Project::GetCurrentProject()->GetProjectDir().string().c_str());

			if (!file.empty())
			{
				std::filesystem::path projDir = Project::GetCurrentProject()->GetProjectDir();
				std::filesystem::path scriptDir = Project::GetCurrentProject()->GetScriptsDir();

				Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddPath(std::filesystem::relative(file, projDir / scriptDir));
				Project::GetCurrentProject()->GetCurrentScene()->GetStorage().LoadAssembly(file);
			}
		}

		if (ImGui::MenuItem("Reload C# assembly"))
		{
			Project::GetCurrentProject()->GetCurrentScene()->GetStorage().ReloadAssemblies();
		}

		ImGui::EndMenu();
	}

	ImGui::Dummy(ImVec2(3.f, 0.0f));

	static bool sceneSettings = false;
	static bool projSettings = false;
	if (ImGui::BeginMenu("Options"))
	{
		if (ImGui::MenuItem("Scene Settings"))
		{
			const Window& window = Application::Get().GetWindow();

			ImGui::SetNextWindowSize(ImVec2(window.GetWidth() / 2.f, window.GetHeight() / 2.f));
			ImGui::SetNextWindowPos(ImVec2(400, 300));

			sceneSettings = true;
		}

		if (ImGui::MenuItem("Project Settings"))
		{
			const Window& window = Application::Get().GetWindow();

			ImGui::SetNextWindowSize(ImVec2(window.GetWidth() / 2.f, window.GetHeight() / 2.f));
			ImGui::SetNextWindowPos(ImVec2(400, 300));

			projSettings = true;
		}

		ImGui::EndMenu();
	}

	if (projSettings) m_Panels->ProjectSettingsWindow(&projSettings);
	if (sceneSettings) m_Panels->SceneSettingsWindow(&sceneSettings);

	Panels::EndColours();
	ImGui::EndMainMenuBar();
}

void EditorLayer::ViewPort()
{
	Panels::BeginColours();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); // Note(Jorben): Necessary for resizing framebuffer
	ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_None);

	ImVec2 size = ImGui::GetContentRegionAvail();
	if (size.x != 0 && size.y != 0) //Check if window is collapsed
		m_FrameBuffer->Resize((uint32_t)size.x, (uint32_t)size.y);

	ImGui::Image(reinterpret_cast<void*>(m_FrameBuffer->GetColorAttachmentRendererID()), size, { 0, 1 }, { 1, 0 });

	//Update viewport size
	Window& window = Application::Get().GetWindow();

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
	ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

	// TODO(Jorben): When SceneRenderer is created, set ViewportWidth for separate renderers
	window.SetViewportWidth((uint32_t)ImGui::GetWindowSize().x);
	window.SetViewportHeight((uint32_t)ImGui::GetWindowSize().y);
	window.SetViewportX((uint32_t)relativePos.x);
	window.SetViewportY((uint32_t)relativePos.y);

	Vec2<float> buttonSize(24.f, 24.f);

	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2.0f - buttonSize.x, 6.0f));

	if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(Panels::s_ButtonTex->GetRendererID()), ImVec2(buttonSize.x, buttonSize.y), { 0, 1 }, { 1, 0 }))
	{
		if (m_Running)
		{
			m_Project->GetCurrentScene()->ResetStorage();
		}
		else
		{
			m_Project->GetCurrentScene()->GetStorage().ReloadAssemblies();
			m_Project->GetCurrentScene()->CopyStorage();
		}
		m_Running = !m_Running;
		Panels::SwitchButtons();
	}

	Panels::EndColours();
	ImGui::PopStyleVar(1);
	ImGui::End();
}

bool EditorLayer::KeyEvent(KeyPressedEvent& e)
{
	if (e.GetKeyCode() == CR_KEY_S && Input::IsKeyPressed(CR_KEY_LEFT_CONTROL))
		SaveProject();

	return false;
}

bool EditorLayer::WindowClose(WindowCloseEvent& e)
{
	SaveProject();

	return false;
}
