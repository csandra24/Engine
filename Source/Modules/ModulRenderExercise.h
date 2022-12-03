#ifndef __ModulRenderExercise_H__
#define __ModulRenderExercise_H__

#include "Module.h"
#include "../Globals.h"
#include "../lib/MathGeoLib_Source/Geometry/Frustum.h"

typedef unsigned __int8 Uint8;

class ModulRenderExercise : public Module
{
public:
	ModulRenderExercise();
	~ModulRenderExercise();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	unsigned Triangle();
	unsigned renderTriangle(unsigned VBOTr, unsigned Program);

private:
	const Uint8* keyboard = NULL;
	unsigned int VBOTr ;

	float4x4 model, view, proj;
};

#endif