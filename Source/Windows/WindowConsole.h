#pragma once
#ifndef __Console__
#define __Console__

#include "Menu.h"

class WindowConsole : public Menu
{
public:
	WindowConsole();
	~WindowConsole();

	void Clear() { buf.clear(); lineOffsets.clear(); }
	void AddLog(const char* log);
	void Draw() override;

	bool IsEnabled() const {
		return enabled;
	}

	bool IsFocused() const {
		return focused;
	}

	void ToggleEnabled() {
		enabled = !enabled;
	}

private:
	ImGuiTextBuffer     buf;
	ImVector<int>       lineOffsets;
	bool                scrollToBottom = true;
};

#endif 
