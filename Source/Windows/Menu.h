#pragma once
#include "../lib/imgui-docking/imgui.h"

class Menu
{
public:
	Menu();
	~Menu();

	virtual void Draw() { }

	

protected:
	bool enabled = true;
	bool focused = false;
};

