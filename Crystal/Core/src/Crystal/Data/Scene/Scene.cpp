#include "crpch.h"
#include "Scene.hpp"

namespace Crystal
{

	Scene::Scene(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::OnUpdate(Timestep& ts)
	{
	}

	void Scene::OnRenderRuntime()
	{
	}

	void Scene::OnRenderEditor()
	{
	}

	void Scene::OnEvent(Event& e)
	{
	}

}