#include "../Globals.h"
#include "../Application.h"
#include "ModuleTexture.h"




ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Start() {
	return true;
}

bool ModuleTexture::CleanUp()
{
	return true;
}

GLuint ModuleTexture::LoadTexture(const char* texture_file)
{
	AVISO("Loading texture from path: \"%s\".", texture_file);

	image = new DirectX::ScratchImage;
	DirectX::ScratchImage* flip = new DirectX::ScratchImage;

	DirectX::FlipRotate(flip->GetImages(), flip->GetImageCount(), flip->GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, *image);


	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLint internalFormat, format, type, Break;
	switch (metadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		Break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		AVISO("Unsupported format");
		break;
	}

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, metadata.width, metadata.height, 0, format, type, image->GetImage(0,0,0)->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;

}
