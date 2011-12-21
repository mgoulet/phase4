/////////////////////////////////////////////////////////////////
//Author: mg goulet
//EnginePhase4.h (engine kernel class)
/////////////////////////////////////////////////////////////////

#ifndef ENGINEPHASE4_H
#define ENGINEPHASE4_H

//kernel subcomponents
#include "KernelStateMachine.h"
#include "GameStateMachine.h"
#include "EngineSubSet.h"
#include "SettingsSubSet.h"

/////////////////////////////////////////////////////////////////
//class definition
class EnginePhase4
{

public:
	//constructors/destructor
	EnginePhase4();
	~EnginePhase4();

	//methods called from driver class
	bool RunEngineSlice();
	bool FireDrivenInput(int fwKeys_down);
	bool FireKillRequest();
	bool FireResizeWindow(int iWidth, int iHeight);
	bool FireDeviceRequest();

	//accessors
	const KernelStateMachine& GetKernelStateMachine() const;
	const GameStateMachine& GetGameStateMachine() const;
	const EngineSubSet& GetEngineSubSet() const;
	const SettingsSubSet& GetSettingsSubSet() const;


private:
	//member variables
	KernelStateMachine kernelstatemachine;
	GameStateMachine gamestatemachine;
	EngineSubSet enginesubset;
	SettingsSubSet settingssubset;

};

#endif ENGINEPHASE4_H