#include "../Globals.h"
#include "../Application.h"
#include "ModuleCamera.h"
#include "ModuleTimer.h"
#include "ModuleInput.h"

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

	frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum->SetViewPlaneDistances(0.1f, 200.0f);
	frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, SCREEN_WIDTH / SCREEN_HEIGHT);

	frustum->SetPos(float3(0.0f, 1.0f, -2.0f));
	frustum->SetFront(-float3::unitZ);
	frustum->SetUp(float3::unitY);

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


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	return true;
}