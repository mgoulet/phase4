/////////////////////////////////////////////////////////////////
//author: martin goulet
//KernelSettings.cpp
/////////////////////////////////////////////////////////////////

#include "KernelSettings.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

KernelSettings::KernelSettings()
{
	this->Init();
}

KernelSettings::~KernelSettings()
{
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool KernelSettings::Init()
{
	//default values for window screen
	this->iAppWidth = 1024;
	this->iAppHeight = 768;
	this->iWinBits = 32;
	this->exit = false;
	this->fullscreen = true;
	//console settings
	this->consolesettings[0] = 1.0f;
	this->consolesettings[1] = 0.0f;
	this->consolesettings[2] = 0.0f;
	this->consolesettings[3] = 0.5f;
	//general text color
	this->generaltextcolor[0] = 1.0f;
	this->generaltextcolor[1] = 1.0f;
	this->generaltextcolor[2] = 0.2f;
	//key polling interval
	this->fKeyPollInterval = 50.f;
	//font
	this->fontname = "Vrinda";
	this->iFontSize = 22;
	this->fov = 80;
	this->skysphere = true;
	this->models3d = true;
	this->math3d = false;

	return true;
}

bool KernelSettings::Release()
{
	//empty for now
	//...

	return true;
}

