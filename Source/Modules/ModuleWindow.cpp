#include "../Globals.h"
#include "../Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	AVISO("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		AVISO("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{

		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		else if (BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		else if (RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}
		

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			AVISO("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	AVISO("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}


void ModuleWindow::SetResizable(bool resizable)
{
	if (resizable)
	{
		SDL_SetWindowResizable(window, SDL_TRUE);
	}
	else
	{
		SDL_SetWindowResizable(window, SDL_FALSE);
	}
}

void ModuleWindow::SetSize(int width, int height)
{
	int display_index = SDL_GetWindowDisplayIndex(window);
	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(display_index), SDL_WINDOWPOS_CENTERED_DISPLAY(display_index));
}

int ModuleWindow::GetWidth() const
{
	int width;
	int height;
	SDL_GetWindowSize(window, &width, &height);
	return width;
}

int ModuleWindow::GetHeight() const
{
	int width;
	int height;
	SDL_GetWindowSize(window, &width, &height);
	return height;
}



