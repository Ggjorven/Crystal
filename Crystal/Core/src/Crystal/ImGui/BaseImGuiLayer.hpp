#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/Layer.hpp"

namespace Crystal
{

	class BaseImGuiLayer : public Layer
	{
	public:
		BaseImGuiLayer();
		virtual ~BaseImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};

}