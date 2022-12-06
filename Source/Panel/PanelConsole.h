#pragma once
#ifndef __LOGCONSOLE_H__
#define __LOGCONSOLE_H__

#include "Panel.h"

class PanelConsole : public Panel
{
public:

	PanelConsole();
	~PanelConsole();

	void Draw();

};

#endif