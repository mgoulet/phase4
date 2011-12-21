//////////////////////////////////////////
//author: martin goulet
//RawInput.cpp
//////////////////////////////////////////

#include "RawInput.h"

extern HWND hWnd;

//////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
//////////////////////////////////////////

RawInput::RawInput()
{
	//empty
}

RawInput::~RawInput()
{
	//empty
}

//////////////////////////////////////////
//METHODS
//////////////////////////////////////////

bool RawInput::InitInputDevices()
{
	//init variables
	for (int i = 0; i < 256; i++)
	{
		this->m_KeyBuffer[i] = 0;
		this->m_SwitchPermission[i] = false;
		this->m_KeySticky[i] = false;
		this->m_KeyFired[i] = false;
	}

	//init DirectInput stuff
	this->m_pDirectInputObject = NULL;
	this->m_pDirectInputKeyboardDevice = NULL;

	//directinput object management
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pDirectInputObject,NULL)))
	{
		return false;
	}

	if(FAILED(m_pDirectInputObject->CreateDevice(GUID_SysKeyboard,&m_pDirectInputKeyboardDevice,NULL)))
	{
		return false;
	}

	//keyboard device
	if(FAILED(m_pDirectInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}

	//set cooperative level
	if(FAILED(m_pDirectInputKeyboardDevice->SetCooperativeLevel(hWnd,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		return false;
	}

	if(FAILED(m_pDirectInputKeyboardDevice->Acquire()))
	{
		return false;
	}

	//mouse device
	if (FAILED(m_pDirectInputObject->CreateDevice(GUID_SysMouse, &g_pDirectInputMouseDevice, NULL)))
	{
		return false;
	}
	//set mouse data format
	if (FAILED(g_pDirectInputMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return false;
	}
	//set cooperative level
	if (FAILED(g_pDirectInputMouseDevice->SetCooperativeLevel(hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		return false;
	}

//	if (FAILED(g_pDirectInputMouseDevice->SetProperty(

	//setup boffer stuff
	DIPROPDWORD         dipdw;
	HRESULT             hres;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 10;
	g_pDirectInputMouseDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
}

bool RawInput::ReleaseInputDevices()
{
	//if needed, release DirectInput object
	if (this->m_pDirectInputObject != NULL)
	{
		this->m_pDirectInputObject->Release();
		this->m_pDirectInputObject = NULL;
	}

	return true;
}


bool RawInput::AcquireDevices()
{
	this->g_pDirectInputMouseDevice->Acquire();
	this->m_pDirectInputKeyboardDevice->Acquire();

	return true;
}

bool RawInput::UpdateKeyboard()
{
	//update key polling
	if(FAILED(m_pDirectInputKeyboardDevice->GetDeviceState(sizeof(this->m_KeyBuffer),(LPVOID)&this->m_KeyBuffer)))
	{
		return false;
	}
	//update toggled states
	this->UpdateToggledKeyTypes();

	return true;
}

bool RawInput::UpdateMouse()
{
if (g_pDirectInputMouseDevice->GetDeviceState(sizeof(diMouseState), &diMouseState) == DI_OK)
{
  if (diMouseState.rgbButtons[0] & 0x80)
  {
    if (!ClickHandled) 
	{
        ClickHandled = TRUE;
		this->bmouseleft = true;
		//MessageBox(NULL,"LEFT!","TEST",NULL);
	}
  }
  else
  {
	  ClickHandled = FALSE;
	  this->bmouseleft = false;
  }

  if (diMouseState.rgbButtons[1] & 0x80)
  {
    if (!ClickHandled) 
	{
		
        ClickHandled = TRUE;
		this->bmouseright = true;
		//MessageBox(NULL,"RIGHT!","TEST",NULL);
	}
  }
  else
  {
	  ClickHandled = FALSE;
	  this->bmouseright = false;
  }
  MouseX = diMouseState.lX;
  MouseY = diMouseState.lY;
}

	//RESET MOUSE TO COORDS (300,300);
	SetCursorPos(300,300);

  
	return true;
}


bool RawInput::KeyPressed(int Key) const
{
	if(this->m_KeyBuffer[Key] & 0x80)
	{
		return true;
	}
	return false;
}

bool RawInput::KeySticky(int Key) const
{
	return this->m_KeySticky[Key];
}

bool RawInput::KeyFired(int Key) const
{
	return this->m_KeyFired[Key];
}

bool RawInput::MouseButtonPressed(int Key) const
{
	if (this->diMouseState.rgbButtons[Key] & 0x80)
	{
		return true;
	}
	return false;
}

LONG RawInput::GetMouseX() const
{
	return this->MouseX;
}

LONG RawInput::GetMouseY() const
{
	return this->MouseY;
}

bool RawInput::LeftMousePressed() const
{
	return this->bmouseleft;
}

bool RawInput::RightMousePressed() const
{
	return this->bmouseright;
}


bool RawInput::UpdateToggledKeyTypes()
{
	for (int i = 0; i < 256; i++)
	{
		//no permission to switch
		if (!this->m_SwitchPermission[i])
		{
			//set permission to switch since no message was launched
			if (!this->m_KeyBuffer[i])
			{
				this->m_SwitchPermission[i] = true;
				this->m_KeyFired[i] = false;
			}
			//lock the state
			else
			{
				this->m_KeyFired[i] = false;
			}
		}
		//permission to switch
		else
		{
			//and switch command, so flip
			if (this->m_KeyBuffer[i])
			{
				//flip sticky state
				this->m_KeySticky[i] = !this->m_KeySticky[i];
				//enable fired key
				this->m_KeyFired[i] = true;
				//remove permission to switch again
				this->m_SwitchPermission[i] = false;
			}
			else
			{
				//remove fired state, since only true a single frame
				this->m_KeyFired[i] = false;
				//do nothing
			}
		}
	}

	return true;
}
