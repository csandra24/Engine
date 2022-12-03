#ifndef __Globals_H__
#define __Globals_H__

#include <windows.h>
#include <stdio.h>

#include <iostream>

#define AVISO(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);
/*void logFPS(float deltaTime);*/

extern std::string logs;
/*extern int FPSIndex;
extern float logsFPS[];
extern float logsMiliseconds[];*/

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum class KeyState 
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

//Constants................
#define MAX_BUF_SIZE 4096
#define DEGTORAD 0.01745329251f
#define RADTODEG 1.0f / DEGTORAD

// Configuration -----------
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 620
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Super Awesome Engine"

#endif