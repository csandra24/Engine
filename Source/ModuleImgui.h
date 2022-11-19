#ifndef __ModuleImgui_H__
#define __ModuleImgui_H__


#include "Module.h"
#include "Globals.h"
#include "./Windows/WindowConsole.h"
#include "./Windows/Menu.h"

typedef unsigned __int8 Uint8;

class Menu;
class WindowConsole;

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
	WindowConsole* console = nullptr;

private:

	const Uint8* keyboard = NULL;
	void MainMenu();
	bool exit_app = false;

	std::list<Menu*> menus;


	
};

#endif