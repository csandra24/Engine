#include "../Globals.h"
#include "../Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleImgui.h"
#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	AVISO("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		AVISO("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;
    
    mouseMotion = { 0,0 };
    mouseWheel = 0;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;

            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;

            case SDL_MOUSEMOTION:
                
                break;

            case SDL_MOUSEWHEEL:
                if (sdlEvent.wheel.y > 0) // scroll up
                {
                    //AVISO("UP");
                    mouseWheel = sdlEvent.wheel.x;
                }
                else if (sdlEvent.wheel.y < 0) // scroll down
                {
                    //AVISO("DOWN");
                    mouseWheel = sdlEvent.wheel.y;
                }
                break;

            case SDL_MOUSEBUTTONUP:

                break;
        }
    }

    keyboard = SDL_GetKeyboardState(NULL);

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	AVISO("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
