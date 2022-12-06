#ifndef __Application_H__
#define __Application_H__

#include <list>
#include "Globals.h"
#include "./Modules/Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleEditor;
class ModuleProgram;
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

	//Configuration Panel
	int max_fps = 60;
	bool limit_framerate = true;
	bool vsync = true;


public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTimer* timer = nullptr;
	ModuleInput* input = nullptr;
	ModuleEditor* Editor = nullptr;
	ModuleProgram* program = nullptr;
	ModuleDebugDraw* draw = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleTexture* textures = nullptr;
	

private:

	std::list<Module*> modules;
	float deltaTime = 0.0f;

};

extern Application* App;

#endif