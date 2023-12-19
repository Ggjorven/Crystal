#include "Editor.hpp"

#include "Crystal/Utils/CustomTypes.hpp"
#include "Crystal/Renderer/ComputeShader.hpp"

#include <imgui_internal.h>

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

#include <shellapi.h> // TODO(Jorben): Make not windows dependant

EditorLayer::EditorLayer(const ApplicationInfo& appInfo)
{
	Window& window = Application::Get().GetWindow();
	//window.SetVSync(true);

	m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);

	m_Project = CreateRef<Project>("New");
	m_Panels = CreateRef<Panels>(m_Project);

	if (appInfo.ArgCount > 1)
	{
		//CR_CORE_TRACE("{0}, \n\t{1}", appInfo.Args[0], appInfo.Args[1]);

		m_Path = std::filesystem::path(appInfo.Args[0]).parent_path() / std::filesystem::path(appInfo.Args[1]);
	}

	//CR_CORE_TRACE("{0}", m_Path.string());
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
Size=947,541
Collapsed=0
DockId=0x00000005,0

[Window][Objects]
Pos=0,19
Size=331,226
Collapsed=0
DockId=0x00000003,0

[Window][Properties]
Pos=0,247
Size=331,473
Collapsed=0
DockId=0x00000004,0

[Window][Content Browser]
Pos=333,562
Size=947,158
Collapsed=0
DockId=0x00000006,0

[Docking][Data]
DockSpace     ID=0x8B93E3BD Window=0xA787BDB4 Pos=112,154 Size=1280,701 Split=X
  DockNode    ID=0x00000001 Parent=0x8B93E3BD SizeRef=331,701 Split=Y Selected=0x967E7699
    DockNode  ID=0x00000003 Parent=0x00000001 SizeRef=223,226 Selected=0x967E7699
    DockNode  ID=0x00000004 Parent=0x00000001 SizeRef=223,473 HiddenTabBar=1 Selected=0x199AB496
  DockNode    ID=0x00000002 Parent=0x8B93E3BD SizeRef=947,701 Split=Y Selected=0x13926F0B
    DockNode  ID=0x00000005 Parent=0x00000002 SizeRef=947,541 CentralNode=1 HiddenTabBar=1 Selected=0x13926F0B
    DockNode  ID=0x00000006 Parent=0x00000002 SizeRef=947,158 Selected=0xBF096F38
	)";

	ImGuiIO& io = ImGui::GetIO();
	io.WantSaveIniSettings = true;

	ImGui::ClearIniSettings();
	ImGui::LoadIniSettingsFromMemory(settings, std::strlen(settings));

	settings = ImGui::SaveIniSettingsToMemory();
	io.WantSaveIniSettings = false;

	UI::Init();

	// Test
	m_Texture = Texture2D::Create(512, 512);
	m_Texture->Bind(0);

	// Example data creation
	std::vector<glm::vec4> textureData(512 * 512, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));  // Adjust based on your data format
	//texture->SetData(textureData.data(), sizeof(float) * textureData.size());

	// Define compute shader source code
	std::string computeShaderSource = R"(
    #version 430

layout(set = 0, binding = 0) buffer InputBuffer {
    vec4 inputData[];
};

layout(set = 0, binding = 1) buffer OutputBuffer {
    vec4 outputData[];
};

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

void main() {
    uint index = gl_GlobalInvocationID.x;

    if (index < inputData.length()) {
        vec3 color = inputData[index].rgb;

        // Calculate the center of the image along the Y-axis
        float centerY = float(inputData.length()) / 2.0;

        // Define the thickness of the red line
        float lineLength = 512.0;

        // Check if the current pixel is within the line
        if (abs(float(index) - centerY) < lineLength) {
            color = vec3(1.0, 0.0, 0.0); // Set the color to red
        }

        outputData[index] = vec4(color, inputData[index].a);
    }
}


)";

	// Create and use the compute shader
	Ref<ComputeShader<glm::vec4, glm::vec4>> computeShader = CreateComputeShader<glm::vec4, glm::vec4>(computeShaderSource);
	computeShader->SetGroupSize(1, 1, 1); // Adjust according to your input size
	computeShader->CreateOutputBuffer(textureData.size() * sizeof(glm::vec4));

	//computeShader->SetUniformFloat("time", 100.0f);

	// Bind the compute shader
	computeShader->Bind();
	computeShader->SetInputBuffer(textureData);
	computeShader->Dispatch(textureData.size(), 1, 1, sizeof(glm::vec4) * textureData.size());
	std::vector<glm::vec4> results = computeShader->GetResults(); // Assuming each element represents RGBA
	m_Texture->SetData(results);
	computeShader->UnBind();
}

void EditorLayer::OnDetach()
{
	//SaveProject();
}

void EditorLayer::OnUpdate(Timestep& ts)
{
	if (m_Project->SettingNewScene())
	{
		m_Panels->SetStartUp(true);
	}

	m_Project->SetState((m_Running ? Project::State::Runtime : Project::State::Editor));
	m_Project->OnUpdate(ts);

	// AutoSave
	if (!m_Running)
	{
		if (m_AutoSaveTimer < CR_AUTOSAVE_INTERVAL)
		{
			m_AutoSaveTimer = m_AutoSaveTimer + ts;
		}
		else
		{
			SaveProject();
			m_AutoSaveTimer = 0.0f;
		}
	}
}

void EditorLayer::OnRender()
{
	m_FrameBuffer->Bind();
	RendererCommand::Clear();

	m_Project->OnRender();
	Renderer2D::DrawQuad({ 100.0f, 100.0f }, { 512.f, 512.f }, m_Texture, false, m_Project->GetCurrentScene()->GetEditorCamera()->GetCamera());

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
	m_Panels->ContentBrowserWindow();

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

void EditorLayer::CreateNewProject() // TODO(Jorben): Fix...
{
	std::string path = Utils::OpenDirectory(Project::GetCurrentProject()->GetProjectDir().parent_path().string().c_str());
	Utils::ReplaceBackSlashes(path);

	if (!path.empty())
	{
		std::filesystem::path newPath = std::filesystem::relative(std::filesystem::path(path), Application::Get().GetWorkingDirectory());

		std::filesystem::path projPath = newPath / "new.crproj";
		m_Path = projPath;

		// Create the parent directories if they don't exist
		std::filesystem::create_directories(projPath.parent_path());
		std::ofstream outFile(projPath);

		if (outFile.good() && outFile.is_open())
		{
			outFile << "Project: Empty" << std::endl;
			outFile.close();
		}
		else
		{
			CR_CORE_ERROR("Error: Unable to open file for writing. {0}, \t{1}", projPath.string(), std::strerror(errno));
		}

		if (!std::filesystem::create_directory(newPath / "Assets")) CR_CORE_ERROR("Failed to create Assets folder.");
		if (!std::filesystem::create_directory(newPath / "Scenes")) CR_CORE_ERROR("Failed to create Scenes folder.");
		if (!std::filesystem::create_directory(newPath / "Scripts")) CR_CORE_ERROR("Failed to create Scripts folder.");
		
		OpenProject(projPath);
	}
}

void EditorLayer::OpenProject(std::filesystem::path path)
{
#if defined(CR_DIST) // TODO(Jorben): Change this for distribution ... also the Crystalizer/Projects path
	std::string CRPath = Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Dist-windows-x86_64\\Crystalizer\\Crystalizer.exe");

#elif defined(CR_RELEASE)
	std::string CRPath = Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Release-windows-x86_64\\Crystalizer\\Crystalizer.exe");
#elif defined(CR_DEBUG)
	std::string CRPath = Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Debug-windows-x86_64\\Crystalizer\\Crystalizer.exe");
#else
	#error No proper configuration selected.
#endif

	//std::filesystem::path projsPath = std::filesystem::path(Utils::GetEnviromentVariable("CRYSTAL_DIR")) / std::filesystem::path("Crystalizer/Projects/");

	CR_CORE_TRACE("{0}", CRPath);
	CR_CORE_TRACE("{0}", path.string());
	CR_CORE_TRACE("{0}", path.parent_path().string());
	//CR_CORE_TRACE("{0}", projsPath.string());

	m_Project.reset();
	//m_Project = nullptr;
	//delete m_Project.get();

	m_Panels->SetStartUp(true);

	m_Project = CreateRef<Project>("");
	if (!path.empty())
	{
		ProjectSerializer serializer(m_Project);
		serializer.Deserialize(path);
	}


	//ShellExecuteA(NULL, "open", CRPath.c_str(), path.string().c_str(), path.string().c_str(), SW_SHOWDEFAULT);

	//Application::Get().DispatchEvent<WindowCloseEvent>();
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
		if (ImGui::MenuItem("New project", "Ctrl+N"))
		{
			CreateNewProject();
		}

		if (ImGui::MenuItem("Open project", "Ctrl+O"))
		{
			std::string file = Utils::OpenFile(".crproj\0*.crproj\0All Files\0*.*\0", m_Project->GetProjectDir().parent_path().string().c_str());

			if (!file.empty())
			{
				OpenProject(std::filesystem::path(file));
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
			std::string file = Utils::OpenFile(".dll\0*.dll", m_Project->GetProjectDir().string().c_str());

			if (!file.empty())
			{
				std::filesystem::path projDir = m_Project->GetProjectDir();
				std::filesystem::path scriptDir = m_Project->GetScriptsDir();

				m_Project->GetCurrentScene()->GetStorage().AddPath(std::filesystem::relative(file, projDir / scriptDir));
				m_Project->GetCurrentScene()->GetStorage().LoadAssembly(file);
			}
		}

		if (ImGui::MenuItem("Reload C# assembly"))
		{
			m_Project->GetCurrentScene()->GetStorage().ReloadAssemblies();
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
		static SceneProperties startScene;
		if (m_Running)
		{
			m_Project->GetCurrentScene()->ResetStorage();

			if (startScene != m_Project->GetCurrentScene()->GetProperties())
			{
				m_Panels->SetStartUp(true);
				m_Project->SetScene(startScene);
			}
		}
		else
		{
			startScene = m_Project->GetCurrentScene()->GetProperties();

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
	if (e.GetKeyCode() == CR_KEY_N && Input::IsKeyPressed(CR_KEY_LEFT_CONTROL))
		CreateNewProject();
	else if (e.GetKeyCode() == CR_KEY_O && Input::IsKeyPressed(CR_KEY_LEFT_CONTROL))
	{
		std::string file = Utils::OpenFile(".crproj\0*.crproj\0All Files\0*.*\0", m_Project->GetProjectDir().parent_path().string().c_str());
		if (!file.empty())
		{
			OpenProject(std::filesystem::path(file));
		}
	}
	else if (e.GetKeyCode() == CR_KEY_S && Input::IsKeyPressed(CR_KEY_LEFT_CONTROL))
		SaveProject();

	return false;
}

bool EditorLayer::WindowClose(WindowCloseEvent& e)
{
	SaveProject();

	return false;
}
