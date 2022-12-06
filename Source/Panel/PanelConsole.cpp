#include "../Application.h"
#include "../Globals.h"
#include "PanelConsole.h"
#include "../Modules/ModuleEditor.h"
#include "../Modules/ModuleWindow.h"

#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"

PanelConsole::PanelConsole()
{

}

PanelConsole::~PanelConsole()
{

}

void PanelConsole::Draw()
{
	if (App->Editor->consoleEnabled) {

		ImGui::SetNextWindowSize(ImVec2(1030, 100), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0, 530), ImGuiCond_Once);

		if (ImGui::Begin("Console")) {
			ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::TextUnformatted(logs.c_str());
			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			{
				ImGui::SetScrollHereY(1.0f);
			}
			ImGui::EndChild();
		}

		ImGui::End();
	}
}