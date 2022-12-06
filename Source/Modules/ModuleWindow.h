#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "../lib/SDL/include/SDL.h"
#include <vector>

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	inline void SetWindowResizable(const bool& resize) const { resize ? SDL_SetWindowResizable(window, SDL_TRUE) : SDL_SetWindowResizable(window, SDL_FALSE); }
	inline void SetWindowBorderless(const bool& borders) const { borders ? SDL_SetWindowBordered(window, SDL_TRUE) : SDL_SetWindowBordered(window, SDL_FALSE); }
	inline void SetWindowFullscreen(const bool& full) const { full ? SDL_SetWindowFullscreen(window, SDL_TRUE) : SDL_SetWindowFullscreen(window, SDL_FALSE); }

	void SetResizable(bool resizable);
	void SetSize(int width, int height);
	int GetWidth() const;
	int GetHeight() const;

	float GetBrightness() const { return SDL_GetWindowBrightness(window); }
	void SetBrightness(float& brightness){ SDL_SetWindowBrightness(window, brightness); }
	bool GetResizable() const { return (SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE) != 0;}


public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;

private:

};

#endif // __ModuleWindow_H__