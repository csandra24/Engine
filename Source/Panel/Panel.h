#pragma once
#ifndef __PANEL_H__
#define __PANEL_H__

class Panel
{

public: 

	Panel()
	{
	}

	virtual bool Init()
	{
		return true;
	}

	virtual void Draw() = 0;

	virtual bool CleanUp()
	{
		return true;
	}

};

#endif