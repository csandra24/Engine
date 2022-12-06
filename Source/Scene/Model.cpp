#include "../Globals.h"
#include "../Application.h"
#include "Model.h"
#include "../Modules/ModuleTexture.h"

#include "../lib/assimp/include/assimp/ai_assert.h"
#include "../lib/assimp/include/assimp/scene.h"
#include "../lib/assimp/include/assimp/cimport.h"
#include "../lib/assimp/include/assimp/postprocess.h"
#include "../lib/MathGeoLib_Source/Math/float4x4.h"

Model::Model(const char* file_name)
{
	Load(file_name);
}

Model::~Model()
{

}


void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++) 
	{
		meshes[i]->Draw(materials);
	}
}

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		AVISO("Loading materials and meshes");
		LoadMaterials(scene->mMaterials, scene->mNumMaterials);
		LoadMesh(scene->mMeshes, scene->mNumMeshes);

	}
	else
	{
		AVISO("Error loading %s: %s", file_name, aiGetErrorString());
	}

}

void Model::LoadMaterials(aiMaterial** aiMaterial, const unsigned int& numMaterials)
{
	AVISO("Loading textures");
	aiString file;
	materials.reserve(numMaterials);

	for (unsigned i = 0; i < numMaterials; ++i)
	{
		if (aiMaterial[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->textures->LoadTexture(file.data));
		}
	}
}

void Model::LoadMesh(aiMesh** aiMesh, const unsigned int& NumMeshes)
{
	AVISO("Loading and creating VBO, EBO and VAO's meshes");
	meshes.reserve(NumMeshes);

	for (unsigned int i = 0; i < NumMeshes; ++i)
	{
		meshes.push_back(new Mesh(aiMesh[i]));
	}

}