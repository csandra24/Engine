#include "../Globals.h"
#include "../Application.h"
#include "ModuleCamera.h"
#include "ModuleTimer.h"
#include "ModuleInput.h"
#include "ModuleDebugDraw.h"

#include "../lib/glew-2.1.0/include/GL/glew.h"
#include "../lib/SDL/include/SDL.h"
#include "SDL_scancode.h"
#include "../lib/MathGeoLib_Source/Math/float2.h"


ModuleCamera::ModuleCamera()
{
	frustum = new Frustum();
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	AVISO("Creating camera");

	aspectRatio = float(SCREEN_WIDTH) / float(SCREEN_HEIGHT);

	frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum->SetViewPlaneDistances(0.1f, 1000.0f);
	frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, aspectRatio);

	frustum->SetPos(float3(0.0f, 1.0f, -2.0f));
	frustum->SetFront(-float3::unitZ);
	frustum->SetUp(float3::unitY);

	proj = frustum->ProjectionMatrix();
	view = frustum->ViewMatrix();

	return true;
}

update_status ModuleCamera::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
	float deltaTime = App->timer->getDeltaTime();
	const float2& mouseMotion = App->input->getMouseMotion();
	const float mouseWheel = App->input->getMouseWheel();

	// WASD + QE
	if (App->input->getKey(SDL_SCANCODE_Q)) //Up
	{
		//AVISO("UP");
		frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * .1f * movementSpeed * deltaTime);

		if (App->input->getKey(SDL_SCANCODE_LSHIFT)) { movementSpeed *= 2; }
	}

	if (App->input->getKey(SDL_SCANCODE_E)) //Down
	{
		AVISO("Down");
		frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * -.1f * movementSpeed * deltaTime);

		if (App->input->getKey(SDL_SCANCODE_LSHIFT)) { movementSpeed *= 2; }
	}

	if (App->input->getKey(SDL_SCANCODE_W)) //Forward
	{
		AVISO("Forward");
		frustum->SetPos(frustum->Pos() + frustum->Front() * 0.1f * movementSpeed * deltaTime);

		if (App->input->getKey(SDL_SCANCODE_LSHIFT)) { movementSpeed *= 2; }
	}

	if (App->input->getKey(SDL_SCANCODE_S)) //Backward
	{
		AVISO("Backward");
		frustum->SetPos(frustum->Pos() + frustum->Front() * -0.1f * movementSpeed * deltaTime);

		if (App->input->getKey(SDL_SCANCODE_LSHIFT)) { movementSpeed *= 2; }
	}

	if (App->input->getKey(SDL_SCANCODE_A)) //Left
	{
		AVISO("Left");
		frustum->SetPos(frustum->Pos() + frustum->WorldRight() * -0.1f * movementSpeed * deltaTime);

		if (App->input->getKey(SDL_SCANCODE_LSHIFT)) { movementSpeed *= 2; }
	}

	if (App->input->getKey(SDL_SCANCODE_D)) //Right
	{
		AVISO("Right");
		frustum->SetPos(frustum->Pos() + frustum->WorldRight() * 0.1f * movementSpeed * deltaTime);

		if (App->input->getKey(SDL_SCANCODE_LSHIFT)) { movementSpeed *= 2; }
	}

	if (App->input->getKey(SDL_SCANCODE_F)) //Reset
	{
		frustum->SetPos(float3(0.0f, 3.0f, 10.0f));
		frustum->SetFront(-float3::unitZ);
		frustum->SetUp(float3::unitY);
	}


	// Rotation (Arrows)
	if (App->input->getKey(SDL_SCANCODE_UP))
	{
		frustum->SetFront(float3x3::RotateAxisAngle(frustum->WorldRight(), rotate * DEGTORAD * deltaTime) * frustum->Front().Normalized());
		frustum->SetUp(float3x3::RotateAxisAngle(frustum->WorldRight(), rotate * DEGTORAD * deltaTime) * frustum->Up().Normalized());
	}

	if (App->input->getKey(SDL_SCANCODE_DOWN))
	{
		frustum->SetFront(float3x3::RotateAxisAngle(frustum->WorldRight(), -rotate * DEGTORAD * deltaTime) * frustum->Front().Normalized());
		frustum->SetUp(float3x3::RotateAxisAngle(frustum->WorldRight(), -rotate * DEGTORAD * deltaTime) * frustum->Up().Normalized());
	}

	if (App->input->getKey(SDL_SCANCODE_LEFT))
	{
		frustum->SetFront(float3x3::RotateY(rotate * DEGTORAD * deltaTime) * frustum->Front().Normalized());
		frustum->SetUp(float3x3::RotateY(rotate * DEGTORAD * deltaTime) * frustum->Up().Normalized());
		frustum->WorldRight();
	}

	if (App->input->getKey(SDL_SCANCODE_RIGHT))
	{
		frustum->SetFront(float3x3::RotateY(-rotate * DEGTORAD * deltaTime) * frustum->Front().Normalized());
		frustum->SetUp(float3x3::RotateY(-rotate * DEGTORAD * deltaTime) * frustum->Up().Normalized());
		frustum->WorldRight();
	}


	// Mouse Wheel (Zoom)
	if (mouseWheel)
	{
		
	}





	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    delete frustum;
	return true;
}


float4x4 ModuleCamera::GetProjectionMatrix() const 
{
	return frustum->ProjectionMatrix();
}

float4x4 ModuleCamera::GetViewMatrix() const 
{
	return frustum->ViewMatrix();
}

void ModuleCamera::SetHorizontalFOV(float Fov)
{
	frustum->SetHorizontalFovAndAspectRatio(Fov, frustum->AspectRatio());
}

void ModuleCamera::SetVerticalFOV(float Fov)
{
	frustum->SetHorizontalFovAndAspectRatio(Fov, frustum->AspectRatio());
}

void ModuleCamera::SetPlaneDistance(float Near, float Far)
{
	frustum->SetViewPlaneDistances(Near, Far);
}

void ModuleCamera::SetAspectRatio(const float width, const float height)
{
	frustum->SetHorizontalFovAndAspectRatio(frustum->HorizontalFov(), width / height);
}

void ModuleCamera::LookAt(const float& x, const float& y, const float& z)
{
	frustum->SetFront(vec(x, y, z));
}


