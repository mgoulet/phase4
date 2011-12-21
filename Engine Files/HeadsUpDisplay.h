/////////////////////////////////////////////////////////////////
//author: martin goulet
//HeadsUpDisplay.h
/////////////////////////////////////////////////////////////////

#ifndef HEADSUPDISPLAY_H
#define HEADSUPDISPLAY_H

//includes
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include "EngineMechanics.h"
#include "EngineEntities.h"
#include "FontManager.h"
#include "EntitySet.h"
#include "SettingsSubSet.h"

using std::string;
using std::stringstream;


const static float DEG2RAD = 3.14159/180;
const static float RADAR_RADIUS = 220;

//class declaration
class HeadsUpDisplay
{
public:
	HeadsUpDisplay();
	~HeadsUpDisplay();

	bool RenderHUD(const FontManager& fontmanager_ref, const EntitySet& entityset_ref, const KernelSettings kernelsettings_ref) const;

private:

	bool DrawHuds(const FontManager& fontmanager_ref, const EntitySet& entityset_ref, const KernelSettings kernelsettings_ref) const;
	bool DisplayCameraAndControlInfo(const FontManager& fontmanager_ref, const EntitySet& entityset_ref, const KernelSettings kernelsettings_ref) const;
	bool DrawHyperRadar(const FontManager&fontmanager_ref, const EntitySet& entityset_ref, const KernelSettings& kernelsettings_ref) const;
	bool DrawCrossHair(const KernelSettings& kernelsettings_ref) const;
};


#endif HEADSUPDISPLAY_H