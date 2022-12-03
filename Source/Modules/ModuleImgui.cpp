#include "../Globals.h"
#include "../Application.h"
#include "ModuleImgui.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"

#include <iostream>
using namespace std;

ModuleImgui::ModuleImgui()
{
}

// Destructor
ModuleImgui::~ModuleImgui()
{
}



// Called before render is available
bool ModuleImgui::Init()
{
	
	AVISO("Creating context Imgui");

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls  

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();

	//Load Font
	
	

	return true;
}

void ModuleImgui::Start() 
{
}

// Called every draw update
update_status ModuleImgui::PreUpdate()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	MainMenu();
	LogConsole();
	//Configuration();
	About();   

	StyleImgui();

	return UPDATE_CONTINUE;
}

update_status ModuleImgui::Update()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);

	if (exit_app)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

update_status ModuleImgui::PostUpdate()
{
	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleImgui::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleImgui::MainMenu() {
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

void ModuleImgui::LogConsole()
{
	if (consoleEnabled) {

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

void ModuleImgui::About()
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

//void ModuleImgui::Configuration()
//{
//	if (configurationEnabled) {
//
//		ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Once);
//		ImGui::SetNextWindowPos(ImVec2(400, 18), ImGuiCond_Once);
//
//		if (ImGui::Begin("Configuration")) {
//			
//			// FPS GRAPH
//			if (ImGui::CollapsingHeader("Application"))
//			{
//				char title[25];
//					sprintf_s(title, 25, "Framerate %.1f", logsFPS[FPSIndex]);
//					ImGui::PlotHistogram("##framerate", &logsFPS[0], 100, FPSIndex, title, 0.0f, 100.0f, ImVec2(310, 100));
//					sprintf_s(title, 25, "Miliseconds %.1f", logsMiliseconds[FPSIndex]);
//					ImGui::PlotHistogram("##miliseconds", &logsMiliseconds[0], 100, FPSIndex, title, 0.0f, 40.0f, ImVec2(310, 100));
//			}
//
//			//WINDOW OPTIONS
//
//			// HARDWARE
//
//		}
//	}
//	
//		
//}


void ModuleImgui::StyleImgui()
{
	ImGui::GetStyle().WindowBorderSize = 0.0f;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	
}
