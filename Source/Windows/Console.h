#ifndef __Console__
#define __Console__

#include "Window.h"

class WConsole : public Window
{
public:
	WConsole();
	~WConsole();

	void				Clear() { buf.clear(); lineOffsets.clear(); }
	void				AddLog(const char* log);
	void				Draw() override;

private:
	ImGuiTextBuffer     buf;
	ImVector<int>       lineOffsets;
	bool                scrollToBottom = true;
};

#endif 
