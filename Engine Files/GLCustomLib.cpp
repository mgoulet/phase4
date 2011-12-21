/////////////////////////////////////////////////////////////////
//author: martin goulet
//GLCustomLib.cpp
/////////////////////////////////////////////////////////////////

#include "GLCustomLib.h"
using namespace GLCustomLib;

bool GLCustomLib::SetupPixelFormatDescriptor(HDC hdc)
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{	
		sizeof(PIXELFORMATDESCRIPTOR),	// size
			1,							// version
			PFD_SUPPORT_OPENGL |		// OpenGL window
			PFD_DRAW_TO_WINDOW |		// render to window
			PFD_DOUBLEBUFFER,			// support double-buffering
			PFD_TYPE_RGBA,				// color type
			32,							// prefered color depth
			0, 0, 0, 0, 0, 0,			// color bits (ignored)
			0,							// no alpha buffer
			0,							// alpha bits (ignored)
			0,							// no accumulation buffer
			0, 0, 0, 0,					// accum bits (ignored)
			16,							// depth buffer
			0,							// no stencil buffer
			0,							// no auxiliary buffers
			PFD_MAIN_PLANE,				// main layer
			0,							// reserved
			0, 0, 0,					// no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
	return true;
}

bool GLCustomLib::GLPrepareForFrame(int width, int height, float fov)
{

	//calculate viewport matrix
	glViewport(0,0,(GLsizei)width, (GLsizei)height);	
	//clear & setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//setup fov
	if ( (fov > 0) && (fov <= 200) )
		gluPerspective(fov, width/height, 1.0, 100000.0);
	else
		gluPerspective(60, width/height, 1.0, 100000.0);
	glColor3f(1.0F, 1.0F, 1.0F);
	//switch to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	return true;
}

