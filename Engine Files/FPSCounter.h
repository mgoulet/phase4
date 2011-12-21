//////////////////////////////////////////
//author: martin goulet
//FPSCounter.h
//////////////////////////////////////////

#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

//for arglist manipulations
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>
#include "Glee.h"
#include <gl/glu.h>
#include <ctime>

#include "GLCustomLib.h"
#include "SubComponent.h"

//empty class declarations
#include "Timer.h"
#include "KernelSettings.h"
#include "FontManager.h"

class FPSCounter: public SubComponent
{
private:

	/////////////////////////////////////////////////
	//THESE MEMBERS ARE MUTED - THEY ARE PRIVATE AND
	//THEREFORE SECURE FROM OUTER MODIFICATION, BUT
	//NEED TO BE MODOFIED FROM THIS VERY CLASS TO
	//PERFORM CERTAIN OPERATIONS.
	//...
	//current output string
	mutable char output[256];
	//frame count for one second
	mutable int iframecount;
	//last time ComputeFPS was called
	mutable float flasttime;
	//fps of the last ComputeFPS call
	mutable float flastfps;
	/////////////////////////////////////////////////

	//init/release object
	bool Init();
	bool Release();

	//compute and merge float point FPS value
	//with the string "FPS: "
	bool CreateOutputString(char* output, char* input, ...) const;

public:

	//***CONSTRUCTORS/DESTRUCTOR***
	FPSCounter();
	~FPSCounter();

	//***METHODS***
	char* GetFPS(const Timer& timer_ref) const;
	bool RenderFPS(	const Timer& timer_ref,
					const FontManager& fontmanager_ref,
					const KernelSettings& kernelsettings_ref) const;

	//***ACCESSORS***

};

#endif FPSCOUNTER_H