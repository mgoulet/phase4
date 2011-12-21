////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	MODEL.h
////////////////////////////////////////////////

/*
NOTE:
This class will contain the necessary information
to render a md2 model.  It contains a static md2
loader which will be responsible of loading all
information and converting them to local datastructs
for further processing (rendering).
*/

#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include "Glee.h"
#include <gl/glu.h>
#include "CTargaImage.h"
#include "Md2Structs.h"

using namespace std;

////////////////////////////////////////////////
//CLASS DECLARATION
class MODEL
{
public:

	//***VARIABLES***
	md2_header header;
	md2_texinfo* skins_ptr;
	md2_texcoords* texcoords_ptr;
	md2_tri* triangles_ptr;
	md2_frame* frames_ptr;
	int* glcmds_ptr;
	//texture index
	GLuint tex_index;
	//translate factors
	float fTransX, fTransY, fTransZ;
	//scale factors
	float fScaleX, fScaleY, fScaleZ;
	//number of triangles
	int iNumTris;

	//***CONSTRUCTORS/DESTRUCTOR***
    MODEL();
	~MODEL();
    
	//***METHODS***
	bool Init();
	bool Release();

private:

};

#endif MODEL_H