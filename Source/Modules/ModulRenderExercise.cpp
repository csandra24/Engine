#include "../Globals.h"
#include "../Application.h"
#include "ModulRenderExercise.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "../lib/SDL/include/SDL.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"



using namespace std;


ModulRenderExercise::ModulRenderExercise()
{
	VBOTr = 0;
}

// Destructor
ModulRenderExercise::~ModulRenderExercise()
{
}



// Called before render is available
bool ModulRenderExercise::Init()
{
	VBOTr = Triangle();

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);
	frustum.SetPos(float3(0.0f, 4.0f, 8.0f));
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);

	proj = frustum.ProjectionMatrix();

	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));

	view = frustum.ViewMatrix();

	return true;
}


// Called every draw update
update_status ModulRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModulRenderExercise::Update()
{
	renderTriangle(VBOTr, App->program->linkingProgram);
	App->draw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), SCREEN_WIDTH, SCREEN_HEIGHT);

	return UPDATE_CONTINUE;
}

update_status ModulRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulRenderExercise::CleanUp()
{
	glDeleteBuffers(1, &VBOTr);
	return true;
}

unsigned ModulRenderExercise::Triangle()
{
	float vertices[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // GL_STATIC_DRAW = the data is set only once and used many times.

	return VBO;

}

unsigned ModulRenderExercise::renderTriangle(unsigned VBO, unsigned program)
{
	// TODO: retrieve model view and projection

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &proj[0][0]);

	// TODO: bind buffer and vertex attributes*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	return program;

}