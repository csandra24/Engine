#pragma once
#ifndef __MODEL_H__
#define __MODEL_H__

#include "../Globals.h"
#include "Mesh.h"

#include "../lib/glew-2.1.0/include/GL/glew.h"
#include <assimp/scene.h>

class Model
{
public:
	void Load(const char* file_name);
	void LoadMaterials(aiMaterial** aiMaterial, const unsigned int& numMaterials);
	void LoadMesh(aiMesh** aiMesh, const unsigned int& NumMeshes);

private:
	std::vector<GLuint> materials;
	std::vector<Mesh*> meshes;

};


#endif
