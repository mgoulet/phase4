//////////////////////////////////////////
//author: martin goulet
//NetInput.h
//////////////////////////////////////////

#ifndef NETINPUT_H
#define NETINPUT_H

//includes
#include <windows.h>
#include <dinput.h>
#include <string>
using std::string;

#include "RawInput.h"

class NetInput
{
public:
	NetInput();
	~NetInput();

	bool UpdateGameKeys(const RawInput& rawinput_ref);

	//movement
	bool Throttle() const;
	bool ReverseThrottle() const;
	bool RollLeft() const;
	bool RollRight() const;
	bool StrafeUp() const;
	bool StrafeDown() const;
	bool StrafeLeft() const;
	bool StrafeRight() const;
	//firing buttons
	bool FirePrimary() const;
	bool FireSecondary() const;
	//hyper factor
	bool HyperUp() const;
	bool HyperDown() const;
	//mouse movements
	LONG GetMouseX() const;
	LONG GetMouseY() const;
	//camera/target cycling
	bool CycleCameraUp() const;
	bool CycleCameraDown() const;
	bool CycleTargetUp() const;
	bool CycleTargetDown() const;

private:

	//bools determining the state of the game events
	bool throttle;
	bool reversethrottle;
	bool rollleft;
	bool rollright;
	bool strafeup;
	bool strafedown;
	bool strafeleft;
	bool straferight;
	bool fireprimary;
	bool firesecondary;
	bool hyperup;
	bool hyperdown;
	//misc
	bool cyclecameraup;
	bool cyclecameradown;
	bool cycletargetup;
	bool cycletargetdown;

	LONG MouseX;
	LONG MouseY;

};

#endif NETINPUT_H