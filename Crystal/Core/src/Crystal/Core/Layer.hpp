#pragma once

#include <string>

#include "Crystal/Core/Core.hpp"

#include "Crystal/Events/Event.hpp"

namespace Crystal
{

	class Layer
	{
	public:
		Layer(const std::string& LayerName = "Default Layer");
		virtual ~Layer() = default;
		
		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(Timestep& ts) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}