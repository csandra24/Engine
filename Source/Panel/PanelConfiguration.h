#pragma once
#ifndef __PANELCONFIGURATION_H__
#define __PANELCONFIGURATION_H__

#include "Panel.h"
#include <dxgi1_4.h>

class PanelConfiguration : public Panel
{
public:

	PanelConfiguration();
	~PanelConfiguration();

	void Draw();

private:

	int windowWidth = 0;
	int windowHeight = 0;

	const char* gpu_vendor;
	const char* rendererS;
	const char* OpenlGlVersion;

	DXGI_QUERY_VIDEO_MEMORY_INFO local_video_memory_info;

};

#endif
