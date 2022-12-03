#pragma once
#ifndef __MODULETEXTURE_H__
#define __MODULETEXTURE_H__


#include "Module.h"
#include "../Globals.h"

#include "../lib/glew-2.1.0/include/GL/glew.h"


class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	bool CleanUp();

	GLuint LoadTexture(const char* file_texture);

private:

};

#endif
