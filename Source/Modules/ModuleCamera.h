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

	vec GetFront() const { return frustum->Front(); }
	vec GetUp() const { return frustum->Up(); }
	vec GetPosition() const { return frustum->Pos(); }
	float GetNearPlane() const { return frustum->NearPlaneDistance();}
	float GetFarPlane() const { return frustum->FarPlaneDistance(); }
	float GetVerticalFOV() const { return frustum->VerticalFov(); }
	inline float GetMoveSpeed() const { return movementSpeed; }
	inline float GetRotateSpeed() const { return rotate; }

	void SetHorizontalFOV(float Fov);
	void SetVerticalFOV(float Fov);
	void SetPlaneDistance(float Near, float Far);
	void SetAspectRatio(const float width, const float height);
	void SetPosition(const vec& position) { frustum->SetPos(position); }
	inline void SetMoveSpeed(const float& setmove) { movementSpeed = setmove; }
	inline void SetRotSpeed(const float& setrotation) { rotate = setrotation; }

	void LookAt(const float& x, const float& y, const float& z);
	void WindowResized(unsigned width, unsigned height);



public:

	float movementSpeed = 10.0f;
	float rotate = 25.0f;
	

private:

	Frustum* frustum;
	float4x4 model, proj, view;

	float aspectRatio;

	float focus_distance = 0.0f;

};


#endif