/////////////////////////////////////////////////////////////////
//Author: mg goulet
//KernelStateMachine.h
/////////////////////////////////////////////////////////////////

#ifndef KERNELSTATEMACHINE_H
#define KERNELSTATEMACHINE_H

//kernel states
#include "KernelStates.h"
#include "GameStateMachine.h"
#include "EngineSubSet.h"
#include "SettingsSubSet.h"
//gl custom lib
#include "GLCustomLib.h"
using namespace GLCustomLib;

//class definition
class KernelStateMachine
{
public:
	//constructors/destructor
	KernelStateMachine(GameStateMachine& gsm_ref, EngineSubSet& ess_ref, SettingsSubSet& sss_ref);
	~KernelStateMachine();

	//methods called from enginephase4 class
	bool ExecuteState();
	int GetKernelState() const;

	//external triggers
	bool FireDrivenInput(int fwKeys_down) const;
	bool FireKillRequest() const;
	bool FireResizeWindow(int iWidth, int iHeight) const;

private:

	//state variables
	KernelState currentstate;

	GameStateMachine& gsm_ref;
	EngineSubSet& ess_ref;
	SettingsSubSet& sss_ref;

	//direct state methods
	bool RunLoadingState();
	bool RunIdleState();
	bool RunConsoleState();
	bool RunGameState();

};

#endif KERNELSTATEMACHINE_H


