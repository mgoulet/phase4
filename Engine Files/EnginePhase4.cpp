/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//EnginePhase4.cpp (central engine class)
/////////////////////////////////////////////////////////////////

#include "EnginePhase4.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////
EnginePhase4::EnginePhase4():
kernelstatemachine(this->gamestatemachine, this->enginesubset, this->settingssubset),
gamestatemachine(this->enginesubset, this->settingssubset)
{
	//empty
}

EnginePhase4::~EnginePhase4()
{
	//empty
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool EnginePhase4::RunEngineSlice()
{ 
	
	//send reference of gm to km every slice
	if (!this->kernelstatemachine.ExecuteState()) { return false; }
	//success
	
	return true;
}

//fire methods
bool EnginePhase4::FireDrivenInput(int fwKeys_down)
{
	
	//send driven input to kernel module
	if (!this->kernelstatemachine.FireDrivenInput(fwKeys_down))
	{
		return false;
	}
	
	return true;
}


bool EnginePhase4::FireKillRequest()
{
	
	//send kil lrequest to kernel module
	this->kernelstatemachine.FireKillRequest();
	
	return true;
}

bool EnginePhase4::FireResizeWindow(int iWidth, int iHeight)
{
	//where the heck did it go?!?

	return true;
}

bool EnginePhase4::FireDeviceRequest()
{
	this->enginesubset.inputmanager.AcquireDevices();

	return true;
}

//accessors
const KernelStateMachine& EnginePhase4::GetKernelStateMachine() const
{
	return this->kernelstatemachine;
}


const GameStateMachine& EnginePhase4::GetGameStateMachine() const
{
	return this->gamestatemachine;
}

const EngineSubSet& EnginePhase4::GetEngineSubSet() const
{
	return this->enginesubset;
}

const SettingsSubSet& EnginePhase4::GetSettingsSubSet() const
{
	return this->settingssubset;
}



