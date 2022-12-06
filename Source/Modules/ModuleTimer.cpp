#include "../Globals.h"
#include "../Application.h"
#include "ModuleTimer.h"
#include "ModuleEditor.h"
#include "SDL.h"

bool ModuleTimer::Init()
{
	AVISO("Time starts");
	previousTime = SDL_GetTicks();
	return true;
}

update_status ModuleTimer::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleTimer::Update()
{
	float atmTime = SDL_GetTicks();
	deltaTime = (atmTime - previousTime) / 1000;
	previousTime = atmTime;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleTimer::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool ModuleTimer::CleanUp()
{
	return true;
}