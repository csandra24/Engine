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

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const;
	void SetHorizontalFOV(float Fov);
	void SetVerticalFOV(float Fov);
	void SetPlaneDistance(float Near, float Far);
	void SetAspectRatio(const float width, const float height);
	void LookAt(const float& x, const float& y, const float& z);
	void WindowResized(unsigned width, unsigned height);

private:

	Frustum* frustum;
	float4x4 model, proj, view;

	float aspectRatio;
	float movementSpeed = 10.0f;
	float rotate = 25.0f;

	float focus_distance = 0.0f;

};


#endif