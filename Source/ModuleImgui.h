#ifndef __ModuleImgui_H__
#define __ModuleImgui_H__


#include "Module.h"
#include "Globals.h"
#include "./Windows/MenuConsole.h"
#include "./Windows/Menu.h"

typedef unsigned __int8 Uint8;

class Menu;
class MenuConsole;

class ModuleImgui : public Module
{
public:

	ModuleImgui(bool start_enabled = true);
	~ModuleImgui();

	bool Init();
	void Start();
	update_status PreUpdate() override;
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();	

	void LogConsole(const char* log) const;

	//windows
	MenuConsole* console = nullptr;

private:

	const Uint8* keyboard = NULL;
	void MainMenu();
	bool exit_app = false;

	std::list<Menu*> menus;


	
};

#endif