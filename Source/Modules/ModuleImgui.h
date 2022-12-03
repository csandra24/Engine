#ifndef __ModuleImgui_H__
#define __ModuleImgui_H__


#include "Module.h"
#include "../Globals.h"

typedef unsigned __int8 Uint8;

class ModuleImgui : public Module
{
public:

	ModuleImgui();
	~ModuleImgui();

	bool Init();
	bool Start();
	update_status PreUpdate() override;
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void LogConsole();
	void About();
	//void Configuration();
	void StyleImgui();
	

private:

	const Uint8* keyboard = NULL;
	void MainMenu();
	bool exit_app = false;
	bool consoleEnabled = true;
	bool aboutEnabled = false;
	bool configurationEnabled = true;
	
};

#endif