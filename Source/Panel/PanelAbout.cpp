#include "../Application.h"
#include "../Globals.h"
#include "PanelAbout.h"
#include "../Modules/ModuleEditor.h"
#include "../Modules/ModuleWindow.h"

#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"

static ImVec4 pink = ImVec4(0.80f, 0.85f, 0.3f, 1.0f);

PanelAbout::PanelAbout()
{

}

PanelAbout::~PanelAbout()
{

}

void PanelAbout::Draw()
{
	if (App->Editor->aboutEnabled) {
		ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0, 18), ImGuiCond_Once);

		if (ImGui::Begin("About"))
		{
			ImGui::Text(TITLE);
			ImGui::Text("");

			ImGui::Text("Description:");
			ImGui::Text("Name Engine");
			ImGui::Text("");

			ImGui::Text("Developed by Sandra Campana");
			ImGui::Text("");

			ImGui::Text("Libraries used:");
			ImGui::Text("- OpenGL 4.6.0");
			ImGui::Text("- SDL 2.0");
			ImGui::Text("- Glew 2.1.0");
			ImGui::Text("- ImGui ");
			ImGui::Text("- MathGeoLib 2021");
			ImGui::Text("- DirectXTex 2022 version");
			ImGui::Text("- Assimp 2021");

			ImGui::Text("");
			ImGui::Text("MIT LICENSE | Copyright (c) 2022 Sandra Campana");
		}
		ImGui::End();
	}
}