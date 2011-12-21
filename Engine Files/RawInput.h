//////////////////////////////////////////
//author: martin goulet
//RawInput.h
//////////////////////////////////////////

#ifndef RAWINPUT_H
#define RAWINPUT_H

//includes
#include <windows.h>
#include <dinput.h>
#include <string>
using std::string;

class RawInput
{
	friend class InputManager;
	friend class NetInput;

public:
	RawInput();
	~RawInput();

	bool InitInputDevices();
	bool ReleaseInputDevices();

	//acquiring devices
	bool AcquireDevices();

	//direct input stuff
	bool UpdateKeyboard();
	bool UpdateMouse();

	bool KeyPressed(int) const;
	bool KeySticky(int) const;
	bool KeyFired(int) const;

	bool MouseButtonPressed(int) const;

	LONG GetMouseX() const;
	LONG GetMouseY() const;

	bool LeftMousePressed() const;
	bool RightMousePressed() const;


private:
	
	//State Machine for toggled keys
	bool UpdateToggledKeyTypes();

	//general input object
	LPDIRECTINPUT8			m_pDirectInputObject;
	//kéyb input object
	LPDIRECTINPUTDEVICE8	m_pDirectInputKeyboardDevice;
	//mouse object
	LPDIRECTINPUTDEVICE8	g_pDirectInputMouseDevice;

	//key arrays
	char					m_KeyBuffer[256];
	bool					m_SwitchPermission[256];	//permission
	bool					m_KeySticky[256];
	bool					m_KeyFired[256];

	//mouse coords
	LONG					MouseX;
	LONG					MouseY;

	//mouse buttons
	bool					bmouseleft;
	bool					bmouseright;

	//mouse polling variables
	DIMOUSESTATE			diMouseState;
	BOOL					ClickHandled;

};


#endif RAWINPUT_H