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
	}

	void RuntimeLayer::OnDetach()
	{
	}

	void RuntimeLayer::OnUpdate(Timestep& ts)
	{
		m_Project->OnUpdate(ts);
	}

	void RuntimeLayer::OnRender()
	{
		RendererCommand::Clear();

		m_Project->OnRender();
	}

	void RuntimeLayer::OnImGuiRender()
	{
	}

	void RuntimeLayer::OnEvent(Event& e)
	{
		m_Project->OnEvent(e);
	}

}