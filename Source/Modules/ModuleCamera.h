#pragma once
#ifndef _MODULECAMERA_
#define _MODULECAMERA_

#include "Module.h"
#include "../lib/MathGeoLib_Source/Geometry/Frustum.h"
#include "../lib/MathGeoLib_Source/Math/float3x3.h"

class Application;

class ModuleCamera : public Module
{
public:

	ModuleCamera();
	virtual ~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:

	Frustum* frustum;
	float4x4 model, proj, view;

};


#endif