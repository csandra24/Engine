#ifndef __ModuleImgui_H__
#define __ModuleImgui_H__


#include "Module.h"
#include "../Globals.h"
#include "../Panel/Panel.h"

#include <list>
#include <vector>

class PanelConsole;

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();
	
	bool Init();
	bool Start();
	update_status PreUpdate() override;
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	
	bool exit_app = false;
	bool consoleEnabled = true;
	bool aboutEnabled = false;
	bool configurationEnabled = false;

	PanelConsole* console = nullptr;


private:
	std::list<Panel*> panels;

	void MainMenu();
	void StyleImgui();
	
	
};

#endif