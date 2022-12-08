#ifndef __Globals_H__
#define __Globals_H__

#include <windows.h>
#include <stdio.h>

#include <iostream>

#define AVISO(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
#define FPSLOGSIZE 100

void log(const char file[], int line, const char* format, ...);

extern std::string logs;
extern int fpsLogIndex;
extern float fpsLog[];
extern float msLog[];

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
#define LOW 0.0167f         
#define HIGH 0.1f   

// Configuration -----------
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FULLSCREEN false
#define BORDERLESS false
#define RESIZABLE false
#define VSYNC true
#define TITLE "Super Effort Engine"

#endif