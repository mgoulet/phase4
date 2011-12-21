/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//FontManager.h
/////////////////////////////////////////////////////////////////

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

//#includes
#include <windows.h>
#include "Glee.h"
#include <gl\glu.h>
#include "SubComponent.h"

#include "KernelSettings.h"

//class definition
class FontManager: public SubComponent
{
public:
	//constructors/destructor
	FontManager();
	~FontManager();
	//create/render text
	bool InitFont(char* fontname, int iSize);
	bool RenderText(const char*, int iX, int iY, const KernelSettings& kernelsettings_ref) const;

private:
	//init/release methods
	bool Init();
	bool Release();

	//memeber variables
	unsigned int base;
	mutable GLuint gluint;


};


#endif FONTMANAGER_H