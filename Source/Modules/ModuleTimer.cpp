#include "../Globals.h"
#include "../Application.h"
#include "ModuleTimer.h"
#include "ModuleEditor.h"
#include "Time/Clock.h"

bool ModuleTimer::Init()
{
	AVISO("Time starts");
	previousTime = float(Clock::Time());
	return true;
}

update_status ModuleTimer::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleTimer::Update()
{
	miliseconds = float(Clock::Time() - previousTime);

	deltaTime = miliseconds / 1000.0f;
	if (deltaTime < LOW) {
		deltaTime = LOW;
	}
	else if (deltaTime > HIGH) {
		deltaTime = HIGH;
	}

	previousTime = float(Clock::Time());

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