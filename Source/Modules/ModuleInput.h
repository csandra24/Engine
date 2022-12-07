#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "../Globals.h"
#include "../lib/MathGeoLib_Source/Math/float2.h"
#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"

#define N_MOUSEBUTTONS 5

enum MouseButton
{
	IDLE,
	UP,
	DOWN
};

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
	const float2& GetMouseMotion() const { return mouseMotion; }
	inline MouseButton GetMouseButton(int id) const { return mouseButtons[id - 1]; }
	const float2 GetMouseWheel() const { return mouseWheel; }
	inline bool GetMouseWheelMove() const { return WheelMove; }

	inline void SetMouseWheel(const bool& wheel) { WheelMove = wheel; }


private:
	const Uint8 *keyboard = NULL;
	MouseButton mouseButtons[N_MOUSEBUTTONS] = { MouseButton::IDLE };
	float2 mouseMotion = { 0, 0 };
	float2 mouse = { 0, 0 };
	float2 mouseWheel = { 0, 0 };
	float mouseWheelIn = 0;
	bool WheelMove = false;
};

#endif