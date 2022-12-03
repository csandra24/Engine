#include "../Globals.h"
#include "../Application.h"
#include "ModuleTexture.h"
#include "../lib/DirectXTex/DirectXTex/DirectXTex.h"



ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{

	return true;
}

bool ModuleTexture::CleanUp()
{
	return true;
}

GLuint ModuleTexture::LoadTexture(const char* texture_file)
{
	AVISO("Loading texture from path: \"%s\".", texture_file);

	GLuint image = LoadTexture("./Game/Textures/Test-Image-Baboon.ppm");

	return true;

}
