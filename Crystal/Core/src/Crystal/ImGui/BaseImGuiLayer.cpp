#include "crpch.h"
#include "BaseImGuiLayer.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Crystal/Core/Application.hpp"
#include "Crystal/Utils/Utils.hpp"

#include "Crystal/Renderer/Renderer.hpp"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <vulkan/vulkan.hpp> // TODO(Jorben): Add vulkan support.

namespace Crystal
{
	Application* Application::s_Instance;



	BaseImGuiLayer::BaseImGuiLayer()
		: Layer("BaseImGuiLayer")
	{
	}

	void BaseImGuiLayer::OnAttach()
	{
		//ImGui Setup
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.IniFilename = NULL;

		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		//TODO add vulkan support
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		//ImGui_ImplGlfw_InitForVulkan(window, true);

		//Load a cool font?
		/* //TODO(Jorben): Fix
		CR_CORE_TRACE("{0}", std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\assets\\fonts\\SulphurPoint-Bold.ttf"));
		io.Fonts->ClearFonts();
		ImFont* font = io.Fonts->AddFontFromFileTTF(std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\assets\\fonts\\SulphurPoint-Bold.ttf").c_str(), 18.0f);
		ImGui::PushFont(font);
		*/
		
	}

	void BaseImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void BaseImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void BaseImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2((float)Application::Get().GetWindow().GetWidth(), (float)Application::Get().GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

}