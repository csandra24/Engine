#ifndef __ModuleRender_H__
#define __ModuleRender_H__


#include "Module.h"
#include "../Globals.h"
#include "../Scene/Model.h"
#include "../lib/MathGeoLib_Source/Geometry/Frustum.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void NewModel(const char* file_name);

	void* context;

	
	inline Model* GetModel() const { return model; }

	void WindowResized(unsigned width, unsigned height);
	void SetVSync(bool vsync);

private:

	Model* model;

};

#endif
