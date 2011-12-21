/////////////////////////////////////////////////////////////////
//author: martin goulet
//KernelSettings.h
/////////////////////////////////////////////////////////////////

#ifndef KERNELSETTINGS_H
#define KERNELSETTINGS_H

#include "GLee.h"
#include <gl\glu.h>
#include "KernelStates.h"
#include "SubComponent.h"

class KernelSettings: public SubComponent
{
public:
	//constructors/destructor
	KernelSettings();
	~KernelSettings();
	//variables
	int iAppWidth;
	int iAppHeight;
	int iWinBits;
	bool exit;
	bool fullscreen;
	//console colors/alpha
	float consolesettings[4];
	float fKeyPollInterval;
	float generaltextcolor[3];
	char* fontname;
	int iFontSize;
	float fov;
	bool skysphere;
	bool models3d;
	bool math3d;

private:
	//methods
	bool Init();
	bool Release();

};


#endif KERNELSETTINGS_H