#include "../Globals.h"
#include "../Application.h"
#include "ModuleProgram.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "../lib/SDL/include/SDL.h"


using namespace std;


ModuleProgram::ModuleProgram()
{}

// Destructor
ModuleProgram::~ModuleProgram()
{}



// Called before render is available
bool ModuleProgram::Init()
{
	return true;
}

bool ModuleProgram::Start() {

	AVISO("Loading shaders");
	unsigned frg_compiled = CompileShader(GL_FRAGMENT_SHADER, LoadShaderSource("FragmentShader.glsl"));
	unsigned vrtx_compiled = CompileShader(GL_VERTEX_SHADER, LoadShaderSource("VertexShader.glsl"));

	Program = LinkShader(vrtx_compiled, frg_compiled);
	return true;
}

// Called before quitting
bool ModuleProgram::CleanUp()
{
	AVISO("Deleting shaders once linked");
	glDeleteProgram(Program);
	
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

unsigned ModuleProgram::CompileShader( GLenum type, const char* source)
{
	
	unsigned shader_id = glCreateShader(type);
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

	unsigned programId = glCreateProgram();
	glAttachShader(programId, vtx_shader);
	glAttachShader(programId, frg_shader);
	glLinkProgram(programId);
	int res;
	glGetProgramiv(programId, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(programId, len, &written, info);
			AVISO("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return programId;

}
