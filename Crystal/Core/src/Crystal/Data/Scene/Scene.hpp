#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

#include "Crystal/ECS/Entity.hpp"
#include "Crystal/ECS/Storage.hpp"

#include <vector>
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

		ECS::Storage m_Storage;
		std::vector<ECS::Entity> m_Entities;

		//Friend classes to be able to use some private members/functions
		friend class SceneSerializer;
	};

}