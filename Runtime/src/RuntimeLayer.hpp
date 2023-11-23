#pragma once

#include <Crystal/Crystal.hpp>

#include <filesystem>

namespace Crystal
{

	class RuntimeLayer : public Layer
	{
	public:
		RuntimeLayer();
		virtual ~RuntimeLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep& ts) override;
		void OnRender() override;

		void OnImGuiRender() override;
		void OnEvent(Event& e);

	private:
		std::filesystem::path m_Path = Utils::GetEnviromentVariable("CRYSTAL_DIR") + "/Crystalizer/Projects/TestProj/test.crproj";

		Ref<Project> m_Project;
	};
}