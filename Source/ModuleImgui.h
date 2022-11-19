#ifndef __ModuleImgui_H__
#define __ModuleImgui_H__


#include "Module.h"
#include "Globals.h"
#include "./Windows/Console.h"
#include "./Windows/Window.h"

typedef unsigned __int8 Uint8;

class Window;
class WConsole;

class ModuleImgui : public Module
{
public:

	ModuleImgui();
	~ModuleImgui();

	bool Init();
	void Start();
	update_status PreUpdate() override;
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();	

	//windows
	WConsole* console = nullptr;

private:

	const Uint8* keyboard = NULL;
	void MainMenu();
	bool exit_app = false;

	std::list<Window*> windows;


	
};

#endif