#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "../Globals.h"
#include "../lib/MathGeoLib_Source/Math/float2.h"

#define N_MOUSEBUTTONS 5

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();
	bool getKey(int id) const { return keyboard[id]; }
	const float GetMouseWheel() const { return mouseWheel; }
	const float2& GetMouseMotion() const { return mouseMotion; }
	inline KeyState GetMouseButton(int id) const { return mouseButtons[id - 1]; }

private:
	const Uint8 *keyboard = NULL;
	KeyState mouseButtons[N_MOUSEBUTTONS] = { KeyState::KEY_IDLE };
	float2 mouseMotion = { 0, 0 };
	float2 mouse = { 0, 0 };
	float mouseWheel = 0;
};

#endif