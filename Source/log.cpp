#pragma once
#include "Globals.h"
#include "Application.h"
#include "./Modules/ModuleEditor.h"


using namespace std;

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);

	logs.append(tmp_string2);
}

void logDeltaMs(float delta_ms)
{
	float fps = 1000.0f / delta_ms;
	fpsLogIndex -= 1;
	if (fpsLogIndex < 0)
	{
		fpsLogIndex = FPSLOGSIZE - 1;
	}
	fpsLog[fpsLogIndex] = fps;
	msLog[fpsLogIndex] = delta_ms;
}


std::string logs;
int fpsLogIndex = FPSLOGSIZE - 1;
float fpsLog[FPSLOGSIZE] = { 0 };
float msLog[FPSLOGSIZE] = { 0 };