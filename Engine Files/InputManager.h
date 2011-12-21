//////////////////////////////////////////
//author: martin goulet
//InputManager.h
//////////////////////////////////////////

/*
NOTE:
This class will be responsible to track which
keys are pressed by the user input. (currently
activated by the windows message system...)
*/

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define DIRECTINPUT_VERSION 0x0800
#pragma comment ( lib, "dinput8.lib")
#pragma comment ( lib, "dinput.lib")
#pragma comment ( lib, "dxguid.lib" )

#include <windows.h>
#include <dinput.h>
#include <string>
#include "EngineMechanics.h"
#include "EngineEntities.h"
#include "SubComponent.h"
#include "RawInput.h"
#include "NetInput.h"

using std::string;

class InputManager: public SubComponent
{
public:
	//constructors/destructor
	InputManager();
	~InputManager();

	//accessors
	const RawInput& GetRawInput() const;
	const NetInput& GetNetInput() const;

	bool UpdateInputDevices();
	bool UpdateGameKeys();
	bool AcquireDevices();

private:

	//RawInput object
	RawInput rawinput;
	//NetInput object
	NetInput netinput;

	bool Init();
	bool Release();

};

#endif INPUTMANAGER_H


