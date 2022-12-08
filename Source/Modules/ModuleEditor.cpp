#pragma once
#include "../Globals.h"
#include "../Application.h"
#include "ModuleEditor.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleTimer.h"

#include "../Panel/PanelConsole.h"
#include "../Panel/PanelAbout.h"
#include "../Panel/PanelConfiguration.h"
#include "../Panel/PanelProperties.h"

#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"

#include <iostream>

using namespace std;



ModuleEditor::ModuleEditor()
{
	
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}



// Called before render is available
bool ModuleEditor::Init()
{
	AVISO("Creating Imgui context");

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls 

	return true;
}

bool ModuleEditor::Start() 
{

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();


	panels.push_back(about = new PanelAbout());
	panels.push_back(configuration = new PanelConfiguration());
	panels.push_back(properties = new PanelProperties());
	panels.push_back(console = new PanelConsole());

	return true;
}

// Called every draw update
update_status ModuleEditor::PreUpdate()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	if (maxFPS.size() >= 100) {
		maxFPS.erase(maxFPS.begin(), maxFPS.begin() + 1);
		msFPS.erase(msFPS.begin(), msFPS.begin() + 1);
	}
	maxFPS.emplace_back(ImGui::GetIO().Framerate);
	msFPS.emplace_back(App->timer->GetMiliseconds());

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{

	MainMenu();
	StyleImgui();

	for (list<Panel*>::iterator it = panels.begin(); it != panels.end(); ++it)
		(*it)->Draw();


	if (exit_app)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);

	SDL_GL_SwapWindow(App->window->window);

	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	for (std::list<Panel*>::iterator it = panels.begin(); it != panels.end(); ++it) { delete (*it);}

	return true;

}

void ModuleEditor::MainMenu() {

	
	// Main Menu
	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://github.com/csandra24/Engine");

			if (ImGui::MenuItem("Download latest"))
				App->RequestBrowser("https://github.com/csandra24/Engine");

			if (ImGui::MenuItem("Report a bug"))
				App->RequestBrowser("https://github.com/csandra24/Engine");

			if (ImGui::MenuItem("About"))
				App->RequestBrowser("https://github.com/csandra24/Engine");

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows")) {
			
			ImGui::MenuItem("Console", "", &consoleEnabled);
			ImGui::MenuItem("About", "", &aboutEnabled);
			ImGui::MenuItem("Configuration", "", &configurationEnabled);
			ImGui::MenuItem("Properties", "", &propertiesEnabled);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Options")) {
			if (ImGui::MenuItem("Exit"))
				exit_app = true;
			ImGui::EndMenu();
			
		}
		
		ImGui::EndMainMenuBar();
	}

}


void ModuleEditor::StyleImgui()
{
	ImGui::GetStyle().WindowBorderSize = 0.0f;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); 
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); //Menu color

	style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.40f, 1.0f);

	style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.0f, 0.0f, 0.40f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.0f, 0.40f, 1.0f);

	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.3f, 0.3f, 0.3f, 0.2f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 0.0f, 0.40f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.0f, 0.0f, 0.40f, 0.5f);

	

	
}


