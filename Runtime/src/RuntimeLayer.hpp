#pragma once

#include <Crystal/Crystal.hpp>

using namespace Crystal;

class RuntimeLayer : public Layer
{
public:
	RuntimeLayer()
		: Layer("Runtime layer")
	{
		m_Scene = CreateRef<Scene>("");
	}
	virtual ~RuntimeLayer()
	{

	}

	void OnAttach() override
	{
		SceneSerializer serializer(m_Scene);

		//serializer.Deserialize("$project$");
	}
	void OnDetach() override
	{

	}

	void OnUpdate(Timestep& ts) override
	{
		m_Scene->OnUpdate(ts);
	}
	void OnRender() override
	{
		m_Scene->OnRenderRuntime();
	}
	void OnImGuiRender() override
	{
	}

	void OnEvent(Event& e)
	{
		m_Scene->OnEvent(e);
	}
	
private:
	Ref<Scene> m_Scene;
};