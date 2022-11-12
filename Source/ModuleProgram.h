#ifndef __ModuleProgram_H__
#define __ModuleProgram_H__

#include "Module.h"
#include "Globals.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


typedef unsigned __int8 Uint8;

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init();
	update_status Update();
	bool CleanUp();

	
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned LinkShader(unsigned vtx_shader, unsigned frg_shader);
	
	unsigned linkingProgram;
	
};



#endif
