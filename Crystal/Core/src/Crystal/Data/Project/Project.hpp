#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Event.hpp"

#include "Crystal/ECS/Entity.hpp"
#include "Crystal/ECS/Storage.hpp"

#include <vector>
#include <string>


namespace Crystal
{

	class Project
	{
	public:
		Project(const std::string& debugName = "");
		virtual ~Project();

		void OnUpdate(Timestep& ts);
		void OnRenderRuntime();
		void OnRenderEditor();
		void OnEvent(Event& e);

		void AddEntity(ECS::Entity& entity) { m_Entities.emplace_back(entity); }
		std::vector<ECS::Entity>& GetEntities() { return m_Entities; }

		ECS::Storage& GetStorage() { return m_Storage; }
		std::string GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;

		ECS::Storage m_Storage;
		std::vector<ECS::Entity> m_Entities;

		//Friend classes to be able to use some private members/functions
		friend class ProjectSerializer;
	};

}