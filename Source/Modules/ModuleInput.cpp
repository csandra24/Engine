#include "../Globals.h"
#include "../Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"

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
                mouseMotion.x = sdlEvent.motion.xrel / (SCREEN_WIDTH / SCREEN_HEIGHT);
                mouseMotion.y = sdlEvent.motion.yrel / (SCREEN_WIDTH / SCREEN_HEIGHT);
                mouse.x = sdlEvent.motion.x / (SCREEN_WIDTH / SCREEN_HEIGHT);
                mouse.y = sdlEvent.motion.y / (SCREEN_WIDTH / SCREEN_HEIGHT);
                break;

            case SDL_MOUSEWHEEL:
                if (sdlEvent.wheel.y > 0) //Scroll Up
                {
                    //llamar camera
                    mouseWheel = sdlEvent.wheel.x;
                }
                else if (sdlEvent.wheel.y < 0) //Scroll Down
                {
                    
                    mouseWheel = sdlEvent.wheel.y;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                mouseButtons[sdlEvent.button.button - 1] = KeyState::KEY_UP;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseButtons[sdlEvent.button.button - 1] = KeyState::KEY_DOWN;
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
