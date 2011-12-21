/////////////////////////////////////////////////////////////////
//author: martin goulet
//GameStateMachine.h
/////////////////////////////////////////////////////////////////

#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

//game states
#include "GameStates.h"
#include "EngineSubSet.h"
#include "SettingsSubSet.h"

//class definition
class GameStateMachine
{
public:
	//constructors/destructor
	GameStateMachine(EngineSubSet& ess_ref, SettingsSubSet& sss_ref);
	~GameStateMachine();

	//methods called by the game class
	bool ExecuteState();

private:

	//game states
	GameState currentstate;
	GameState previousstate;

	//engine subset reference
	EngineSubSet& ess_ref;
	SettingsSubSet& sss_ref;

	//methods called from within this class
	bool RunLoadState();
	bool RunIdleState();
	bool RunMenuState();
	bool RunGameState();

};

#endif GAMESTATEMACHINE_H


