/////////////////////////////////////////////////////////////////
//Author: mg goulet
//(framework taken from book Beginning OpenGL Game Programming)
//win.cpp (main window)
/////////////////////////////////////////////////////////////////

#ifndef WIN_H
#define WIN_H

#include <windows.h>
#include <dinput.h>
#include "Glee.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "EnginePhase4.h"

HDC hDC;
HWND hWnd;
static EnginePhase4 enginephase4;

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static HGLRC hRC;

	// dispatch messages
	switch (uMsg)
	{	
	case WM_ACTIVATE:
		
		//acquire DirectInput devices
		enginephase4.FireDeviceRequest();

		break;

	case WM_CREATE:			// window creation
		hDC = GetDC(hWnd);
		GLCustomLib::SetupPixelFormatDescriptor(hDC);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		break;

	case WM_DESTROY:			// window destroy
	case WM_QUIT:
	case WM_CLOSE:				// windows is closing

		enginephase4.FireKillRequest();
		// deselect rendering context and delete it
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);

		// send WM_QUIT to message queue
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		// send request to resize window
		enginephase4.FireResizeWindow( HIWORD(lParam), LOWORD(lParam) );
		break;

	case WM_PAINT:				// paint
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:		// left mouse button
		//gamemanager_ptr->id_ptr->EnablePosRoll();
		break;

	case WM_RBUTTONDOWN:		// right mouse button
		//gamemanager_ptr->id_ptr->EnableNegRoll();
		break;

	case WM_MOUSEMOVE:			// mouse movement
		break;

	case WM_LBUTTONUP:			// left button release
		//gamemanager_ptr->id_ptr->DisableRoll();
		break;

	case WM_RBUTTONUP:			// right button release
		//gamemanager_ptr->id_ptr->DisableRoll();
		break;

	case WM_KEYDOWN:
		int fwKeys_down;
		LPARAM keyData_down;
		fwKeys_down = (int)wParam;    // virtual-key code 
		keyData_down = lParam;        // key data 

		//check to close application via ESC key
		if (fwKeys_down == VK_ESCAPE)
		{
			//send kill request
			//enginephase4.FireKillRequest();
		}
		else
		{
			//else send input driven action down the engine
			enginephase4.FireDrivenInput(fwKeys_down);
		}

		break;

	case WM_KEYUP:
		int fwKeys_up;
		LPARAM keyData_up;
		fwKeys_up = (int)wParam;    // virtual-key code 
		keyData_up = lParam;        // key data 
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;		// window class
	MSG		   msg;				// message
	DWORD	   dwExStyle;		// Window Extended Style
	DWORD	   dwStyle;			// Window Style
	RECT	   windowRect;

	windowRect.left=(long)0;						// Set Left Value To 0
	windowRect.right=(long)enginephase4.GetSettingsSubSet().GetKernelSettings().iAppWidth;	// Set Right Value To Requested Width
	windowRect.top=(long)0;							// Set Top Value To 0
	windowRect.bottom=(long)enginephase4.GetSettingsSubSet().GetKernelSettings().iAppHeight; // Set Bottom Value To Requested Height

	// fill out the window class structure
	windowClass.cbSize			= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc		= MainWindowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	// default icon
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);		// default arrow
	windowClass.hbrBackground	= NULL;								// don't need background
	windowClass.lpszMenuName	= NULL;								// no menu
	windowClass.lpszClassName	= "GLClass";
	windowClass.hIconSm			= LoadIcon(NULL, IDI_WINLOGO);		// windows logo small icon

	// register the windows class
	if (!RegisterClassEx(&windowClass))
		return 0;

	if (enginephase4.GetSettingsSubSet().GetKernelSettings().fullscreen)	// fullscreen?
	{
		DEVMODE dmScreenSettings;			// device mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);	
		
		dmScreenSettings.dmPelsWidth = enginephase4.GetSettingsSubSet().GetKernelSettings().iAppWidth;			// screen width
		dmScreenSettings.dmPelsHeight = enginephase4.GetSettingsSubSet().GetKernelSettings().iAppHeight;			// screen height
		dmScreenSettings.dmBitsPerPel = enginephase4.GetSettingsSubSet().GetKernelSettings().iWinBits;				// bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// 
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// setting display mode failed, switch to windowed
			MessageBox(NULL, "Display mode failed", NULL, MB_OK);
			//enginephase4.GetEngineSubSet().GetKernelSettings().fullscreen = FALSE;	
		}
	}

//	fullscreen = true;

	if (enginephase4.GetSettingsSubSet().GetKernelSettings().fullscreen)								// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;					// Window Extended Style
		dwStyle=WS_POPUP;						// Windows Style
		ShowCursor(FALSE);						// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// class registered, so now create our window
	hWnd = CreateWindowEx(NULL,				// extended style
		"GLClass",							// class name
		"Phase4 - Copyright 2004 - Martin Goulet",			// app name
		dwStyle | WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,								// x,y coordinate
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, // width, height
		NULL,								// handle to parent
		NULL,								// handle to menu
		hInstance,							// application instance
		NULL);								// no extra params

	hDC = GetDC(hWnd);

	// check if window creation failed (hwnd would equal NULL)
	if (!hWnd)
		return 0;

	ShowWindow(hWnd, SW_SHOW);			// display the window
	UpdateWindow(hWnd);					// update the window

//////////////////////////////////////////////////////////////////////////////////////

	//system loop
	while (!enginephase4.GetSettingsSubSet().GetKernelSettings().exit)
	{
		//run game slice
		if (!enginephase4.RunEngineSlice()) break;
		//swap buffers
		SwapBuffers(hDC);

		//windows message handling system	
		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				if (enginephase4.GetSettingsSubSet().GetKernelSettings().fullscreen)
				{
					ChangeDisplaySettings(NULL,0);			// If So Switch Back To The Desktop
				}

				TranslateMessage (&msg);
				DispatchMessage (&msg);
				return (int)msg.wParam;
				break;
			}
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}

	}

//////////////////////////////////////////////////////////////////////////////////////

	if (enginephase4.GetSettingsSubSet().GetKernelSettings().fullscreen)
	{
		ChangeDisplaySettings(NULL,0);			// If So Switch Back To The Desktop
		ShowCursor(TRUE);						// Show Mouse Pointer
	}

	TranslateMessage (&msg);
	DispatchMessage (&msg);
	return (int)msg.wParam;
}

#endif WIN_H