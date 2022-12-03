#ifndef __Dummy_H__
#define __Dummy_H__

#include "./Modules/Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		AVISO("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		AVISO("Dummy CleanUp!");
		return true;
	}
};

#endif