#pragma once
#include "../lib/imgui-docking/imgui.h"

class Menu
{
public:

	Menu(char* title);
	virtual ~Menu();

	virtual bool Draw() = 0;

	virtual inline void OnOff();
	virtual inline void SetOnOff(bool set) { enabled = set; }
	virtual inline bool IsEnabled() const;
	virtual inline char* GetName() const { return name; }

protected:

	bool enabled = false;
	char* name = nullptr;
};

