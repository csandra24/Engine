#ifndef __Application_H__
#define __Application_H__

#include <list>
#include "Globals.h"
#include "./Modules/Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleImgui;
class ModuleProgram;
class ModulRenderExercise;
class ModuleDebugDraw;
class ModuleCamera;
class ModuleTimer;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(const char* url) const;
	//void LogGui(const char* log) const;


public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTimer* timer = nullptr;
	ModuleInput* input = nullptr;
	ModuleImgui* ImGui = nullptr;
	ModuleProgram* program = nullptr;
	ModulRenderExercise* exercise = nullptr;
	ModuleDebugDraw* draw = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleTexture* textures = nullptr;
	

private:

	std::list<Module*> modules;
	float deltaTime = 0.0f;

};

extern Application* App;

#endif