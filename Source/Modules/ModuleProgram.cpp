#include "../Globals.h"
#include "../Application.h"
#include "ModuleProgram.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "../lib/SDL/include/SDL.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"


using namespace std;


ModuleProgram::ModuleProgram()
{}

// Destructor
ModuleProgram::~ModuleProgram()
{}



// Called before render is available
bool ModuleProgram::Init()
{
	bool ret = true;

	char* vertexShader = LoadShaderSource("VertexShader.glsl");
	char* fragmentShader = LoadShaderSource("FragmentShader.glsl");

	unsigned vrtx_compiled = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned frg_compiled = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glCompileShader(vrtx_compiled);
	glCompileShader(frg_compiled);

	linkingProgram = LinkShader(vrtx_compiled, frg_compiled);

	return ret;

}



update_status ModuleProgram::Update()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleProgram::CleanUp()
{
	glDeleteProgram(linkingProgram);
	
	return true;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* source)
{
	string shaderSource;
	unsigned shader_id = glCreateShader(type);

	//source = (const GLchar*)shaderSource.c_str();
	glShaderSource(shader_id, 1, &source, 0);

	glCompileShader(shader_id);

	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);

		glDeleteShader(shader_id);

		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			AVISO("Log Info: %s", info);
			free(info);
		}
	}
	return shader_id;

}


unsigned ModuleProgram::LinkShader(unsigned vtx_shader, unsigned frg_shader)
{
	unsigned linkingProgram = glCreateProgram();
	glAttachShader(linkingProgram, vtx_shader);
	glAttachShader(linkingProgram, frg_shader);
	glLinkProgram(linkingProgram);
	int res;
	glGetProgramiv(linkingProgram, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(linkingProgram, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(linkingProgram, len, &written, info);
			AVISO("Program Log Info: %s", info);
			free(info);
		}
	}

	glDetachShader(linkingProgram, vtx_shader);
	glDetachShader(linkingProgram, frg_shader);

	return linkingProgram;

}
