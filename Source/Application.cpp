#pragma once
#include "Application.h"
#include "./Modules/ModuleWindow.h"
#include "./Modules/ModuleRender.h"
#include "./Modules/ModuleInput.h"
#include "./Modules/ModuleImgui.h"
#include "./Modules/ModuleProgram.h"
#include "./Modules/ModulRenderExercise.h"
#include "./Modules/ModuleDebugDraw.h"
#include "./Modules/ModuleCamera.h"
#include "./Modules/ModuleTimer.h"
#include "./Modules/ModuleTexture.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(window = new ModuleWindow());
	modules.push_back(timer = new ModuleTimer());
	modules.push_back(input = new ModuleInput());
	modules.push_back(draw = new ModuleDebugDraw());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(textures = new ModuleTexture());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(exercise = new ModulRenderExercise());
	modules.push_back(ImGui = new ModuleImgui());
	modules.push_back(renderer = new ModuleRender());
	
	
	
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;


	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

void Application::RequestBrowser(const char* url) const
{
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}
