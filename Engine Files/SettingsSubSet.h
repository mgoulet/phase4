/////////////////////////////////////////////////////////////////
//Author: mg goulet
//SettingsSubSet.h
/////////////////////////////////////////////////////////////////

#ifndef SETTINGSSUBSET_H
#define SETTINGSSUBSET_H

//includes
#include "KernelSettings.h"
#include "GameSettings.h"

class SettingsSubSet
{
	//friendship classes
	friend class KernelStateMachine;
	friend class GameStateMachine;
	friend class EngineSubSet;

public:
	//constructors/destructor
	SettingsSubSet();
	~SettingsSubSet();

	//NON CONSTANT since most objects have to modify this shit
	const KernelSettings& GetKernelSettings() const;
	const GameSettings& GetGameSettings() const;

private:

	//settings variables
	KernelSettings kernelsettings;
	GameSettings gamesettings;



};

#endif SETTINGSSUBSET_H