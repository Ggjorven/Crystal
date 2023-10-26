#include "Panels.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Utils/Utils.hpp"

#include <glm/glm.hpp>

namespace Crystal
{

	Ref<Texture2D> Panels::s_CheckerboardTex;

	void Panels::Init()
	{
		s_CheckerboardTex = Texture2D::Create("assets/textures/checkerboard.tga");
	}

	void Panels::TexturePanel(const std::string_view& name, Ref<Texture2D>& changeAbleTexture, bool* useTexture)
	{
		if (ImGui::CollapsingHeader(name.data(), nullptr, ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
			ImGui::Image(changeAbleTexture ? (void*)changeAbleTexture->GetRendererID() : (void*)s_CheckerboardTex->GetRendererID(), ImVec2(64, 64), { 0, 1 }, { 1, 0 });
			ImGui::PopStyleVar();

			if (ImGui::IsItemHovered())
			{
				if (changeAbleTexture) //Texture is set
				{
					ImGui::BeginTooltip();

					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(changeAbleTexture->GetPath().c_str());
					ImGui::PopTextWrapPos();
					ImGui::Image((void*)changeAbleTexture->GetRendererID(), ImVec2(384, 384), { 0, 1 }, { 1, 0 });

					ImGui::EndTooltip();
				}

				if (ImGui::IsItemClicked()) //Open a new file/texture
				{
					std::string filename = Utils::OpenFile("");
					CR_TRACE("Selected file: {0}", filename);

					if (filename != "")
					{
						changeAbleTexture.reset(); changeAbleTexture = Texture2D::Create(filename);
					}
				}
			}
			
			if (useTexture) //if not nullptr
			{
				ImGui::SameLine();

				std::string strName = name.data();

				ImGui::BeginGroup();

				std::string use = "Use##" + strName;
				ImGui::Checkbox(use.c_str(), useTexture);

				ImGui::EndGroup();
			}
			//ImGui::SameLine();
			//
			//std::string colour = "Colour##" + strName;
			//ImGui::ColorEdit3(colour.c_str(), glm::value_ptr(m_AlbedoInput.Color), ImGuiColorEditFlags_NoInputs);
			
		}
	}

}