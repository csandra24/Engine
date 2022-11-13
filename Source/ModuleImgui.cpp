#include "Globals.h"
#include "Application.h"
#include "ModuleImgui.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "./lib/SDL/include/SDL.h"
#include "./lib/imgui-docking/imgui.h"
#include "./lib/imgui-docking/imgui_impl_sdl.h"
#include "./lib/imgui-docking/imgui_impl_opengl3.h"
#include "./lib/glew-2.1.0/include/GL/glew.h"


ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.05f, 1.00f);

ModuleImgui::ModuleImgui()
{}

// Destructor
ModuleImgui::~ModuleImgui()
{}



// Called before render is available
bool ModuleImgui::Init()
{

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
	/*io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport
		
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls  */   

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();

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

	return UPDATE_CONTINUE;
}

update_status ModuleImgui::Update()
{

	ImGui::Render();

	ImGuiIO& io = ImGui::GetIO();

	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	return UPDATE_CONTINUE;
}

update_status ModuleImgui::PostUpdate()
{
	SDL_Event event;
	ImGui_ImplSDL2_ProcessEvent(&event);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleImgui::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(App->renderer->context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();
	return true;
}