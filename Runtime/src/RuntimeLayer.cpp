#include "RuntimeLayer.hpp"

namespace Crystal
{

	RuntimeLayer::RuntimeLayer()
		: Layer("Runtime")
	{
		m_Project = CreateRef<Project>("");
	}

	RuntimeLayer::~RuntimeLayer()
	{
	}

	void RuntimeLayer::OnAttach()
	{
		ProjectSerializer serializer(m_Project);
		serializer.Deserialize(m_Path);

		m_Project->SetState(Project::State::Runtime);

		Window& window = Application::Get().GetWindow();
		window.SetVSync(true);

		m_FrameBuffer = FrameBuffer::Create(window.GetWidth(), window.GetHeight(), FrameBufferFormat::RGBA8);
		window.SetViewportX(0u);
		window.SetViewportY(0u);
	}

	void RuntimeLayer::OnDetach()
	{
	}

	void RuntimeLayer::OnUpdate(Timestep& ts)
	{
		m_Project->OnUpdate(ts);

		//Update viewport size
		Window& window = Application::Get().GetWindow();

		// TODO(Jorben): When SceneRenderer is created, set ViewportWidth for separate renderers
		window.SetViewportWidth(window.GetWidth());
		window.SetViewportHeight(window.GetHeight());

		m_FrameBuffer->Resize(window.GetWidth(), window.GetHeight());
	}

	void RuntimeLayer::OnRender()
	{
		const Window& window = Application::Get().GetWindow();
		
		m_FrameBuffer->Bind();
		RendererCommand::Clear();

		m_Project->OnRender();

		m_FrameBuffer->Unbind();

		RendererCommand::ReplaceFramebuffer(m_FrameBuffer);
	}

	void RuntimeLayer::OnImGuiRender()
	{
	}

	void RuntimeLayer::OnEvent(Event& e)
	{
		m_Project->OnEvent(e);
	}

}