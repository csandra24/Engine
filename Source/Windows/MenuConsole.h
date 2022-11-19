#pragma once
#ifndef __Console__
#define __Console__

#include "Menu.h"

#include "../lib/imgui-docking/imgui.h"

class MenuConsole : public Menu
{
public:

	MenuConsole(char* name);
	~MenuConsole();

	bool Draw();

	void AddLog(const char* log);

private:

	void Clear();

private:

	ImGuiTextBuffer buf;
	ImGuiTextFilter filter;
	ImVector<int> lineOffsets;
	bool scrollToBottom = true;
};

#endif 
