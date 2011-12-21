/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//KernelStateMachine.cpp
/////////////////////////////////////////////////////////////////

#include "KernelStateMachine.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

KernelStateMachine::KernelStateMachine(GameStateMachine& gsm_ref,
									   EngineSubSet& ess_ref,
									   SettingsSubSet& sss_ref):
										gsm_ref(gsm_ref),
										ess_ref(ess_ref),
										sss_ref(sss_ref)
{
	//initializing states
	this->currentstate = KERNEL_LOADING;
}

KernelStateMachine::~KernelStateMachine()
{
	//empty
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool KernelStateMachine::ExecuteState()
{
	//UPDATE INPUT (common to all states, so shoved here.)
	ess_ref.inputmanager.UpdateInputDevices();

	//UPDATE SYSTEM TIMER (updated ONCE in each frame)
	this->ess_ref.timer.UpdateTimeInterval();

	//switch box
	switch (this->currentstate)
	{
	case KERNEL_LOADING:	if (!this->RunLoadingState())	return false;	break;
	case KERNEL_CONSOLE:	if (!this->RunConsoleState())	return false;	break;
	case KERNEL_GAME:		if (!this->RunGameState())		return false;	break;
	default:				return false;					break;
	};

	//successful switch completion

	return true;

}

int KernelStateMachine::GetKernelState() const
{
	return this->currentstate;
}

bool KernelStateMachine::FireDrivenInput(int fwKeys_down) const
{
	
	//if the engine is in the console state, shoot up the input 
	//to the console otherwise, the system is not bothered
	
	if (this->currentstate == KERNEL_CONSOLE)
	{
		this->ess_ref.console.ProcessCurrentConsoleMessage(	this->sss_ref.kernelsettings,
															this->sss_ref.gamesettings,
															fwKeys_down);
	}
	else
	{
		return false;
	}
	
	return true;
}

bool KernelStateMachine::FireKillRequest() const
{
	
	//chage exit state
	this->sss_ref.kernelsettings.exit = true;
	
	return true;
}

bool KernelStateMachine::FireResizeWindow(int iWidth, int iHeight) const
{
	/*
	//change parameters in kernel settings
	this->kss_ref.settingsk.iAppWidth = iWidth;
	this->kss_ref.settingsk.iAppHeight = iHeight;
	//reset gl view port
	GLCustomLib::SetupViewPortPerspective(this->kss_ref.settingsk.iAppWidth,
										  this->kss_ref.settingsk.iAppHeight);
	*/
	return true;
}

bool KernelStateMachine::RunLoadingState()
{
	
	//message that engine was initialized properly
	ess_ref.console.AppendToConsole("Engine awakening...");
	//message that initialization of all subkernel members was successful
	ess_ref.console.AppendToConsole("All kernel subcomponents were initialized successfully.");
	//create font
	ess_ref.console.AppendToConsole("Initializing Font from loaded settings...");
	if (!ess_ref.fontmanager.InitFont(sss_ref.GetKernelSettings().fontname, sss_ref.GetKernelSettings().iFontSize)) return false;
	
	//load assets
	if (!(ess_ref.textureset.LoadAssets())) return false;
	ess_ref.console.AppendToConsole("Textures were properly initialized.");

	if (!(ess_ref.modelset.LoadAssets())) return false;
	ess_ref.console.AppendToConsole("Models were properly initialized.");

	//once loaded, change the engine state to CONSOLE
	//should be menu before game, but now straight to GAME state.
	this->currentstate = KERNEL_GAME;

	//success messages
	ess_ref.console.AppendToConsole("Loading phase successful.");
	ess_ref.console.AppendToConsole("Switching KernelState to KERNEL_GAME.");
	ess_ref.console.AppendToConsole("Switching GameState to GAME_GAME.");
	ess_ref.console.AppendToConsole("Ready. Command?");
	
	
	//testing math stuff..
	stringstream ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ss9, ss10;
	string s1, s2, s3,s4,s5,s6,s7,s8,s9, s10;
/*
	MathEntities::M3X3 mat(1,3,8,3,4,5,1,9,8);
	//print det
	float f = MathManipulations::DetMtx3X3(mat);
	ss10 << f;
	ss10 >> s10;
	ess_ref.console.AppendToConsole("Det: " + s10);
	//inverse
	MathManipulations::InvMtx3X3(mat);
	MathManipulations::InvMtx3X3(mat);
	//print test
	ss1 << mat.fCoords[0]; ss1 >> s1;
	ss2 << mat.fCoords[1]; ss2 >> s2;
	ss3 << mat.fCoords[2]; ss3 >> s3;
	ess_ref.console.AppendToConsole("[" + s1 + ", " + s2 + ", "  + s3 + "]");
	ss4 << mat.fCoords[3]; ss4 >> s4;
	ss5 << mat.fCoords[4]; ss5 >> s5;
	ss6 << mat.fCoords[5]; ss6 >> s6;
	ess_ref.console.AppendToConsole("[" + s4 + ", "  + s5 + ", "  + s6 + "]");
	ss7 << mat.fCoords[6]; ss7 >> s7;
	ss8 << mat.fCoords[7]; ss8 >> s8;
	ss9 << mat.fCoords[8]; ss9 >> s9;
	ess_ref.console.AppendToConsole("[" + s7 + ", "  + s8 + ", "  + s9 + "]");
	*/
	
	return true;
}

bool KernelStateMachine::RunConsoleState()
{
	//check for gamestate jump
	if (this->ess_ref.inputmanager.GetRawInput().KeyFired(DIK_GRAVE)) { this->currentstate = KERNEL_GAME; }

	// Setup GL for slice
	GLCustomLib::GLPrepareForFrame(sss_ref.GetKernelSettings().iAppWidth, sss_ref.GetKernelSettings().iAppHeight, sss_ref.GetKernelSettings().fov);

	//give it away to the game state machine
	gsm_ref.ExecuteState();

	//render FPS
	this->ess_ref.fpscounter.RenderFPS(	this->ess_ref.timer,
										this->ess_ref.fontmanager,
										this->sss_ref.GetKernelSettings());

	//render console
	this->ess_ref.console.RenderConsole(this->sss_ref.GetKernelSettings(),
										this->ess_ref.textureset,
										this->ess_ref.fontmanager,
										this->ess_ref.timer);

	return true;
}

bool KernelStateMachine::RunGameState()
{
	//check for console state jump
	if (this->ess_ref.inputmanager.GetRawInput().KeyFired(DIK_GRAVE)) { this->currentstate = KERNEL_CONSOLE; }

	// Setup GL for slice
	GLCustomLib::GLPrepareForFrame(sss_ref.GetKernelSettings().iAppWidth, sss_ref.GetKernelSettings().iAppHeight, sss_ref.GetKernelSettings().fov);	

	//give it away to the game state machine
	gsm_ref.ExecuteState();

	//render FPS
	this->ess_ref.fpscounter.RenderFPS(	this->ess_ref.timer, 
										this->ess_ref.fontmanager,
										this->sss_ref.GetKernelSettings());

	return true;
}
