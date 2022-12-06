#ifndef __ModuleImgui_H__
#define __ModuleImgui_H__


#include "Module.h"
#include "../Globals.h"
#include "../Panel/Panel.h"

#include <list>
#include <vector>

class PanelConsole;
class PanelAbout;
class PanelConfiguration;
class PanelProperties;

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

	void MainMenu();
	
	bool exit_app = false;
	bool consoleEnabled = true;
	bool aboutEnabled = false;
	bool configurationEnabled = true;
	bool propertiesEnabled = true;

	PanelConsole* console = nullptr;
	PanelAbout* about = nullptr;
	PanelConfiguration* configuration = nullptr;
	PanelProperties* properties = nullptr;


private:
	std::list<Panel*> panels;
	
	void StyleImgui();
	
};

#endif