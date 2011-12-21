//////////////////////////////////////////
//author: martin goulet
//SkySphere.h
//////////////////////////////////////////

/*
NOTE:
This class is used to represent the skydome
of the application.
*/

#ifndef SKYSPHERE_H
#define SKYSPHERE_H

#include <windows.h>
#include <cmath>
#include "Glee.h"
#include <gl/glu.h>
#include "CTargaImage.h"
#include "SettingsSubSet.h"
#include "EngineMechanics.h"
#include "EngineEntities.h"
#include "SubComponent.h"
#include "TextureSet.h"

//DEFINITIONS

class SkySphere: public SubComponent
{
private:
	//***Variables***
	float* vDomeArray_ptr;
	//textures
	CTargaImage sky_tex;
	GLuint sky_tex_index;

	//init/release methods
	bool Init();
	bool Release();
	//spherical construction
	bool ConstructSphere();


public:
	//***Constructors/Destructor***
	SkySphere();
	~SkySphere();

	//***Methods***
	bool Render(const TextureSet& textureset_ref, const CAM& c_ref,
				 const SettingsSubSet& sss_ref) const;

};


#endif SKYSPHERE_H