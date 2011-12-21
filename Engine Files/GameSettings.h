/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//GameSettings.h
/////////////////////////////////////////////////////////////////

#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

//includes
#include "SubComponent.h"

class GameSettings: public SubComponent
{
public:
	//constructors/destructor
	GameSettings();
	~GameSettings();

	//game settings variables
	bool hud;

private:
	//init/release methods
	bool Init();
	bool Release();
};

#endif GAMESETTINGS_H