#pragma once
#ifndef __MODULETEXTURE_H__
#define __MODULETEXTURE_H__


#include "Module.h"
#include "../Globals.h"

#include "../lib/glew-2.1.0/include/GL/glew.h"
#include "../lib/DirectXTex/DirectXTex/DirectXTex.h"


class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();
	bool Start();
	bool CleanUp();

	GLuint LoadTexture(const char* file_texture);

	inline DirectX::ScratchImage* GetImage() const { return image; }
	inline DirectX::TexMetadata GetMetadata() const { return metadata; }
	

private:

	DirectX::ScratchImage *image;
	DirectX::TexMetadata metadata;
};

#endif
