//////////////////////////////////////////
//author: martin goulet
//InputManager.cpp
//////////////////////////////////////////

#include "InputManager.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

InputManager::InputManager()
{
	//init class
	this->Init();

}

InputManager::~InputManager()
{
	//release class
	this->Release();

}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

const RawInput& InputManager::GetRawInput() const
{
	return this->rawinput;
}

const NetInput& InputManager::GetNetInput() const
{
	return this->netinput;
}

bool InputManager::UpdateInputDevices()
{
	this->rawinput.UpdateKeyboard();
	this->rawinput.UpdateMouse();
	this->netinput.UpdateGameKeys(this->rawinput);

	return true;
}

bool InputManager::UpdateGameKeys()
{
	this->netinput.UpdateGameKeys(this->rawinput);

	return true;
}

bool InputManager::AcquireDevices()
{
	this->rawinput.AcquireDevices();

	return true;
}

bool InputManager::Init()
{
	this->rawinput.InitInputDevices();

	return true;
}

bool InputManager::Release()
{
	this->rawinput.ReleaseInputDevices();

	return true;
}

