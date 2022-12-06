#pragma once
#ifndef __MESH_H__
#define __MESH_H__

#include <assimp/mesh.h>
#include "../lib/glew-2.1.0/include/GL/glew.h"

#include <vector>

class Mesh
{
public:
	Mesh(const aiMesh* mesh);
	~Mesh();
	void Draw(const std::vector<unsigned>& model_textures);

	inline const int& GetNumVertices() { return numberVertices;}
	inline const int& GetNumIndices() { return num_indices; }
	inline const int& GetMaterialIndex() { return material_index;}

private:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();

	int numberVertices;
	int num_indices;
	int material_index;

	GLuint vbo;
	GLuint ebo;
	GLuint vao;

};

#endif
