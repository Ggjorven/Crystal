#include <Crystal/Crystal.hpp>
#include <imgui.h>

using namespace Crystal;

class FramebufferLayer : public Layer 
{
public:
    FramebufferLayer()
        : m_RenderFramebuffer(nullptr), m_DisplayFramebuffer(nullptr)
    {
    }

    virtual ~FramebufferLayer() {}

    void OnAttach() override
    {
        Window& window = Application::Get().GetWindow();

        m_RenderFramebuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);
        m_DisplayFramebuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);
    }

    void OnDetach() override
    {
        m_RenderFramebuffer.reset();
        m_DisplayFramebuffer.reset();
    }

    void OnUpdate(Timestep& ts) override
    {
    }

    void OnRender() override
    {
        m_RenderFramebuffer->Bind();
        Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        m_RenderFramebuffer->Unbind();
    }

    void OnImGuiRender() override
    {
        static bool p_open = true;

        static bool opt_fullscreen_persistant = true;
        static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
        bool opt_fullscreen = opt_fullscreen_persistant;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = /*ImGuiWindowFlags_MenuBar | */ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        //if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
        //	window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Dockspace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        ImGui::Begin("Viewport");

        auto viewportSize = ImGui::GetContentRegionAvail();
        m_RenderFramebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);

        ImGui::Image((void*)m_RenderFramebuffer->GetColorAttachmentRendererID(), viewportSize, { 0, 1 }, { 1, 0 });
        ImGui::End();

        ImGui::Begin("a");

        viewportSize = ImGui::GetContentRegionAvail();
        m_RenderFramebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);

        ImGui::Image((void*)m_RenderFramebuffer->GetColorAttachmentRendererID(), viewportSize, { 0, 1 }, { 1, 0 });

        ImGui::End();


        ImGui::End();

        ImGui::PopStyleVar();
    }

private:
    Ref<FrameBuffer> m_RenderFramebuffer;
    Ref<FrameBuffer> m_DisplayFramebuffer;

};