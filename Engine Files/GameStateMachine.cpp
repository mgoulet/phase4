/////////////////////////////////////////////////////////////////
//author: martin goulet
//GameStateMachine.cpp
/////////////////////////////////////////////////////////////////

#include "GameStateMachine.h"

/////////////////////////////////////////////////////////////////
//CONSTRCUTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

GameStateMachine::GameStateMachine(EngineSubSet& ess_ref,
								   SettingsSubSet& sss_ref):
									ess_ref(ess_ref),
									sss_ref(sss_ref)
{
	this->currentstate = GAME_GAME;
}

GameStateMachine::~GameStateMachine()
{
	//empty
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool GameStateMachine::ExecuteState()
{
	//switch box
	
	switch (this->currentstate)
	{
	case GAME_LOAD:	if (!this->RunLoadState())	return false;	break;
	case GAME_IDLE:	if (!this->RunIdleState())	return false;	break;
	case GAME_MENU:	if (!this->RunMenuState())	return false;	break;
	case GAME_GAME:	if (!this->RunGameState())	return false;	break;
	default:									return false;	break;
	};
	
	return true;
}

bool GameStateMachine::RunLoadState()
{

	return true;
}

bool GameStateMachine::RunIdleState()
{
	//empty for now, since idle means game shit hit the fan temporarily
	return true;
}

bool GameStateMachine::RunMenuState()
{
	ShowCursor(TRUE);
	//change menu position
	//empty for now until Input is fixed.

	return true;
}

bool GameStateMachine::RunGameState()
{
	//hide cursor
	ShowCursor(FALSE);

	//update game keys
	this->ess_ref.inputmanager.UpdateGameKeys();

	//process game logics and stuff
	this->ess_ref.entitymanager.RunEnvironmentalSlice(	this->ess_ref.timer,
														this->ess_ref.console,
														this->ess_ref.inputmanager,
														this->ess_ref.entityset,
														this->ess_ref.heightmap);
/*
	GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f };
	glFogfv(GL_FOG_COLOR, fogColor);
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 300.0);
	glFogf(GL_FOG_END, 1000.0);
*/
	//render skysphere
	this->ess_ref.skysphere.Render(	this->ess_ref.textureset,
									this->ess_ref.entityset.GetCAM(),
									this->sss_ref);
	//render terrain
	this->ess_ref.heightmap.RenderHeightMap(	this->sss_ref,
												this->ess_ref.textureset,
												this->ess_ref.console,
												this->ess_ref.entityset.GetCAM());

	//render complex map
	this->ess_ref.complexmap.RenderComplexMap(	this->sss_ref,
												this->ess_ref.textureset,
												this->ess_ref.console,
												this->ess_ref.modelset,
												this->ess_ref.entityset.GetCAM());
	//render entities
	this->ess_ref.scenemanager.RenderScene(	this->ess_ref.entityset,
											this->ess_ref.modelset,
											this->ess_ref.textureset,
											this->sss_ref);
	//render hud
	this->ess_ref.headsupdisplay.RenderHUD(	this->ess_ref.fontmanager,
											this->ess_ref.entityset,
											this->sss_ref.kernelsettings);
	
	return true;
}


