/////////////////////////////////////////////////////////////////
//author: martin goulet
//GLCustomLib.h
/////////////////////////////////////////////////////////////////

#include "Glee.h"
#include <gl\glu.h>
#include <windows.h>

#ifndef GLCUSTOMLIB_H
#define GLCUSTOMLIB_H

#pragma comment( lib, "opengl32.lib" )				// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )					// Search For GLu32.lib While Linking
#pragma comment( lib, "vfw32.lib" )					// Search For VFW32.lib While Linking

namespace GLCustomLib
{
	//setup methods
	bool SetupPixelFormatDescriptor(HDC hdc);
	bool GLPrepareForFrame(int width, int height, float fov);

};

#endif GLCUSTOMLIB_H