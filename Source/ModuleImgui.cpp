#include "Globals.h"
#include "Application.h"
#include "ModuleImgui.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "./lib/SDL/include/SDL.h"
#include "./lib/imgui-docking/imgui.h"
#include "./lib/imgui-docking/imgui_impl_sdl.h"
#include "./lib/imgui-docking/imgui_impl_opengl3.h"

ModuleImgui::ModuleImgui()
{}

// Destructor
ModuleImgui::~ModuleImgui()
{}



// Called before render is available
bool ModuleImgui::Init()
{
	return true;
}

void ModuleImgui::Start() 
{
	
}

// Called every draw update
update_status ModuleImgui::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleImgui::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleImgui::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleImgui::CleanUp()
{
	return true;
}
