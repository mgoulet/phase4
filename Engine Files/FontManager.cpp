/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//FontManager.cpp
/////////////////////////////////////////////////////////////////

#include "FontManager.h"

extern HDC hDC;

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

FontManager::FontManager()
{
	//init class
	this->Init();
}

FontManager::~FontManager()
{
	//release class
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool FontManager::InitFont(char* filename, int iSize)
{
	//generate font
	this->base = glGenLists(96);

	//creating font
	HFONT hfont;

	hfont = CreateFont(
		iSize, 0, 0, 0, /*FW_BOLD*/FALSE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH, filename);	

	//error check
	if (!hfont) { return false; }

	//selet object
	SelectObject(hDC, hfont);

	wglUseFontBitmaps(hDC, 32, 96, this->base);

	//generate list
	this->gluint = glGenLists(1);

	return true;
}

bool FontManager::RenderText(const char* string, int iX, int iY, const KernelSettings& kernelsettings_ref) const
{
	//push matrix
	glPushMatrix();
	//push attribs
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//load identity
	glLoadIdentity();
	//blending settings
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//set default text color
	glColor3f(	kernelsettings_ref.generaltextcolor[0],
				kernelsettings_ref.generaltextcolor[1],
				kernelsettings_ref.generaltextcolor[2]);

	//create list
	glNewList(gluint, GL_COMPILE);
	{
		//save states
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//set the list base
		glListBase(base-32);
	
		//set modelview matrix
		glPushMatrix();
		glLoadIdentity();

		//set projection matrix
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f, kernelsettings_ref.iAppWidth, kernelsettings_ref.iAppHeight, 0.0f, -1.0f, 1.0f);

		//set states
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
	}
	glEndList();

	//call list
	glCallList(gluint);
	//set raster position
	glRasterPos2i(iX, iY);
	//call disaply list
	glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);

	//pop attribs
	glPopAttrib();
	//pop matrix
	glPopMatrix();
	return true;
}

bool FontManager::Init()
{
	//init members
	return true;
}

bool FontManager::Release()
{
	//release shit
	glDeleteLists(this->base,96);
	return true;
}