#pragma once
#include "../Globals.h"
#include "../Application.h"
#include "ModuleEditor.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

#include "../Panel/PanelConsole.h"

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

	panels.push_back(console = new PanelConsole());

	return true;
}

// Called every draw update
update_status ModuleEditor::PreUpdate()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

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

		if (ImGui::BeginMenu("File")) {	}

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

/*void ModuleEditor::LogConsole()
{
	
}

void ModuleEditor::About()
{   
	if (aboutEnabled) {
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
			ImGui::Text("- OpenGL");
			ImGui::Text("- MathGeoLib");
			ImGui::Text("- SDL");
			ImGui::Text("- ImGui");
			ImGui::Text("- Glew");
			ImGui::Text("- DirectXTex");
			ImGui::Text("- Assimp");
			ImGui::Text("");
			ImGui::Text("MIT LICENSE | Copyright (c) 2022 Sandra Campana");
		}
		ImGui::End();
	}
}

void ModuleEditor::Configuration()
{
	if (configurationEnabled) {

		ImGui::SetNextWindowSize(ImVec2(1030, 100), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0, 10), ImGuiCond_Once);

		if (ImGui::Begin("Application")) {

			std::vector<float> fpsLog;
			std::vector<float> msLog;

			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", fpsLog[fpsLog.size() - 1]); 
			ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %0.1f", msLog[msLog.size() - 1]);
			ImGui::PlotHistogram("#milliseconds", &msLog[0], msLog.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

		}
		ImGui::End();
	}
		
}*/


void ModuleEditor::StyleImgui()
{
	ImGui::GetStyle().WindowBorderSize = 0.0f;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	
}


