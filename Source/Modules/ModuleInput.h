#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "../Globals.h"
#include "../lib/MathGeoLib_Source/Math/float2.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();
	bool GetKey(int id) const { return keyboard[id]; }
	const float getMouseWheel() const { return mouseWheel; }
	const float2& getMouseMotion() const { return mouseMotion; }

private:
	const Uint8 *keyboard = NULL;

	float2 mouseMotion = { 0, 0 };
	float2 mouse = { 0, 0 };
	float mouseWheel = 0;
};

#endif