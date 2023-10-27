#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

#include <string>

namespace Crystal
{

	class Scene
	{
	public:
		Scene(const std::string& debugName = "");
		virtual ~Scene();

		void OnUpdate(Timestep& ts);
		void OnRenderRuntime();
		void OnRenderEditor();
		void OnEvent(Event& e);

		//ECS stuff ex. CreateEntity

	protected:
		std::string m_DebugName;

		// TODO: ECS storage

		//Friend classes to be able to use some private members/functions
		friend class SceneSerializer;
	};

}