//////////////////////////////////////////
//author: martin goulet
//NetInput.cpp
//////////////////////////////////////////

#include "NetInput.h"


//////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
//////////////////////////////////////////

NetInput::NetInput()
{
	//empty
}

NetInput::~NetInput()
{
	//empty
}

//////////////////////////////////////////
//METHODS
//////////////////////////////////////////

bool NetInput::UpdateGameKeys(const RawInput& rawinput_ref)
{
	//This method will map the keys pressed on the keyboard
	//to actual game events.
	//I will need to establish a config file which will determine
	//which keys will be mapped to which game event.
	//For the moment, there will be a hardcoded configuration map.

/*
	//UPDATE DIRECTIONAL MOVEMENTS
	if (rawinput_ref.KeyPressed(DIK_UP))
	{this->throttle = true;} else {this->throttle = false;}
	if (rawinput_ref.KeyPressed(DIK_DOWN))
	{this->reversethrottle = true;} else {this->reversethrottle = false;}
	if (rawinput_ref.KeyPressed(DIK_LEFT))
	{this->strafeleft = true;} else {this->strafeleft = false;}
	if (rawinput_ref.KeyPressed(DIK_RIGHT))
	{this->straferight = true;} else {this->straferight = false;}
	// UPDATE vertical movement CONTROLS
	if (rawinput_ref.KeyPressed(DIK_RSHIFT))
	{this->strafeup = true;} else {this->strafeup = false;}
	if (rawinput_ref.KeyPressed(DIK_RCONTROL))
	{this->strafedown = true;} else {this->strafedown = false;}
	//UPDATE PRIMARY/SECONDARY FIRE
	if (rawinput_ref.KeyFired(DIK_NUMPAD0))
	{this->fireprimary = true;} else {this->fireprimary = false;}
	if (rawinput_ref.KeyFired(DIK_NUMPAD1))
	{this->firesecondary = true;} else {this->firesecondary = false;}
*/

	//UPDATE DIRECTIONAL MOVEMENTS
	if (rawinput_ref.KeyPressed(DIK_UP))
	{this->throttle = true;} else {this->throttle = false;}
	if (rawinput_ref.KeyPressed(DIK_DOWN))
	{this->reversethrottle = true;} else {this->reversethrottle = false;}
	if (rawinput_ref.KeyPressed(DIK_LEFT))
	{this->strafeleft = true;} else {this->strafeleft = false;}
	if (rawinput_ref.KeyPressed(DIK_RIGHT))
	{this->straferight = true;} else {this->straferight = false;}
	// UPDATE vertical movement CONTROLS
	if (rawinput_ref.KeyPressed(DIK_RSHIFT))
	{this->strafeup = true;} else {this->strafeup = false;}
	if (rawinput_ref.KeyPressed(DIK_RCONTROL))
	{this->strafedown = true;} else {this->strafedown = false;}
	//UPDATE PRIMARY/SECONDARY FIRE
	if (rawinput_ref.KeyFired(DIK_NUMPAD0))
	{this->fireprimary = true;} else {this->fireprimary = false;}
	if (rawinput_ref.KeyFired(DIK_NUMPAD1))
	{this->firesecondary = true;} else {this->firesecondary = false;}

	//hyper factor
	if (rawinput_ref.KeyPressed(DIK_HOME))
	{this->hyperdown = true;} else {this->hyperdown = false;}
	if (rawinput_ref.KeyPressed(DIK_END))
	{this->hyperup = true;} else {this->hyperup = false;}

	//UPDATE ARBITRARY ROTATIONS
	//screen coords
	this->MouseX = rawinput_ref.MouseX;
	this->MouseY = rawinput_ref.MouseY;
	//mouse buttons
	if (rawinput_ref.MouseButtonPressed(0))
	{this->rollleft = true;} else {this->rollleft = false;}
	if (rawinput_ref.MouseButtonPressed(1))
	{this->rollright = true;} else {this->rollright = false;}

	//camera/target cycling
	if (rawinput_ref.KeyFired(DIK_PGUP))
	{this->cyclecameraup = true;} else {this->cyclecameraup = false;}
	if (rawinput_ref.KeyFired(DIK_PGDN))
	{this->cyclecameradown = true;} else {this->cyclecameradown = false;}
	if (rawinput_ref.KeyFired(DIK_INSERT))
	{this->cycletargetup = true;} else {this->cycletargetup = false;}
	if (rawinput_ref.KeyFired(DIK_DELETE))
	{this->cycletargetdown = true;} else {this->cycletargetdown = false;}

	return true;
}

//accessors
bool NetInput::FirePrimary() const { return this->fireprimary; }
bool NetInput::FireSecondary() const { return this->firesecondary; }
bool NetInput::ReverseThrottle() const { return this->reversethrottle; }
bool NetInput::StrafeDown() const { return this->strafedown; }
bool NetInput::StrafeRight() const { return this->straferight; }
bool NetInput::StrafeLeft() const { return this->strafeleft; }
bool NetInput::StrafeUp() const { return this->strafeup; }
bool NetInput::RollLeft() const { return this->rollleft; }
bool NetInput::RollRight() const { return this->rollright; }
bool NetInput::Throttle() const { return this->throttle; }
bool NetInput::HyperUp() const { return this->hyperup; }
bool NetInput::HyperDown() const { return this->hyperdown; }

//mouse movements
LONG NetInput::GetMouseX() const { return this->MouseX; }
LONG NetInput::GetMouseY() const { return this->MouseY; }
bool NetInput::CycleCameraUp() const { return this->cyclecameraup; }
bool NetInput::CycleCameraDown() const { return this->cyclecameradown; }
bool NetInput::CycleTargetUp() const { return this->cycletargetup; }
bool NetInput::CycleTargetDown() const { return this->cycletargetdown; }














