#include "../Application.h"
#include "../Globals.h"
#include "PanelProperties.h"
#include "../Modules/ModuleEditor.h"
#include "../Modules/ModuleTexture.h"
#include "../Modules/ModuleRender.h"
#include "../Scene/Mesh.h"

#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"
#include "../lib/MathGeoLib_Source/Math/float4x4.h"

static ImVec4 pink = ImVec4(1.0f, 0.0f, 0.40f, 1.0f);

PanelProperties::PanelProperties()
{

}

PanelProperties::~PanelProperties()
{

}

void PanelProperties::Draw()
{
	if (App->Editor->propertiesEnabled) {
		ImGui::SetNextWindowSize(ImVec2(260, 200), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(940, 18), ImGuiCond_Once);

		if (ImGui::Begin("Properties"))
		{

			if (ImGui::CollapsingHeader("Geometry"))
			{
				ImGui::TextUnformatted("Meshes");
				for (int i = 0; i < App->renderer->GetModel()->GetMeshes().size(); ++i) {
					ImGui::Text("Vertices");
					ImGui::SameLine();
					ImGui::TextColored(pink, "%u", App->renderer->GetModel()->GetMeshes()[i]->GetNumVertices());
					ImGui::Text("Indices");
					ImGui::SameLine();
					ImGui::TextColored(pink, "%u", App->renderer->GetModel()->GetMeshes()[i]->GetNumIndices());
					ImGui::Text("Material Index");
					ImGui::SameLine();
					ImGui::TextColored(pink, "%u", App->renderer->GetModel()->GetMeshes()[i]->GetMaterialIndex());
				}
			}

			if (ImGui::CollapsingHeader("Texture"))
			{

				ImGui::TextUnformatted("Size of the texture:");
				ImGui::SameLine();
				ImGui::TextColored(pink, std::to_string(App->textures->GetMetadata().width).c_str());
				ImGui::SameLine();
				ImGui::TextColored(pink, "x");
				ImGui::SameLine();
				ImGui::TextColored(pink, std::to_string(App->textures->GetMetadata().height).c_str());

				

			}

		}
		ImGui::End();
	}
}