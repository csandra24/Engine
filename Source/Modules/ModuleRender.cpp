#include "../Globals.h"
#include "../Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "../Scene/Model.h"

#include "../lib/SDL/include/SDL.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"
#include "../lib/MathGeoLib_Source/Math/float4x4.h"

ModuleRender::ModuleRender()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	AVISO("Creating render context");
	context = SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();
	// … check for errors
	AVISO("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0

	AVISO("Vendor: %s", glGetString(GL_VENDOR));
	AVISO("Renderer: %s", glGetString(GL_RENDERER));
	AVISO("OpenGL version supported %s", glGetString(GL_VERSION));
	AVISO("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	return true;
}

bool ModuleRender::Start() 
{
	AVISO("----- ASSIMP STARTS -----");

	
	AVISO("----- LOADING MODEL -----")
	model = new Model("Assets/BakerHouse.fbx");

	return true;
}

update_status ModuleRender::PreUpdate()
{

	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);

	glViewport( 0, 0, w, h);
	
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	model->Draw();
	App->draw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), SCREEN_WIDTH, SCREEN_HEIGHT);

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	AVISO("Destroying render");

	//Destroy window
	SDL_GL_DeleteContext(context);

	delete model;

	return true;
}

void ModuleRender::NewModel(const char* file_path)
{

	delete model;
	model = new Model(file_path);

}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	App->camera->WindowResized(width, height);
}

void ModuleRender::SetVSync(bool vsync)
{
	SDL_GL_SetSwapInterval(vsync);
}
