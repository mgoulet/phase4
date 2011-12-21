//////////////////////////////////////////
//author: martin goulet
//SkySphere.cpp
//////////////////////////////////////////

#include "SkySphere.h"

//////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
//////////////////////////////////////////

SkySphere::SkySphere()
{
	//init class
	this->Init();
}

SkySphere::~SkySphere()
{
	//release texture index
	this->Release();
}


//////////////////////////////////////////
//METHODS
//////////////////////////////////////////

bool SkySphere::Init()
{
	//call creation of dome
	if (this->ConstructSphere())
	{
		return true;
	}
    //failure reached
	return false;
}

bool SkySphere::Release()
{
	//delete texture
	glDeleteTextures(1, &this->sky_tex_index);
	//delete actual skysphere vector data
	delete[] this->vDomeArray_ptr;

	return true;
}

bool SkySphere::ConstructSphere()
{
	/*
	NOTE:
	As opposed to traditional spherical coordinates, I will have to
	interchange the functions of Y and Z, since my Y axis will be
	pointing upwards.
	X = r * Sin(phi) * Cos(theta)
	Y = r * Cos(phi)
	Z = r * Sin(phi) * Sin(theta)
	*/

	//fundamental values
	float fR = 10.0f;
	float fPI = 3.141593;
	float fRPERD = 0.017453293;
	float fNumPhiSteps = /*18*/18;
	float fNumThetaSteps = /*36*/36;
	//compound variables
	float fSizePhiStep = 180.0f/fNumPhiSteps * fRPERD;
	float fSizeThetaStep = 360.0f/fNumThetaSteps * fRPERD;
	float fTotalSteps = fNumPhiSteps * fNumThetaSteps * 4;
	//min & max values for Phi and Theta angles
	float fPhiMin = 0.0f * fRPERD;
	float fPhiMax = 180.0f * fRPERD;
	float fThetaMin = 0.0f * fRPERD;
	float fThetaMax = 360.0f * fRPERD;
	float fArraySize = fTotalSteps * 5;

	//creating vertex array to hold vertices
	this->vDomeArray_ptr = new float[fArraySize*2];
	int iterator = 0;

	//first loop, Phi:
	//start at 270 degrees (4.71239 radiants) and increment up to 90 degrees
	//which is (4.71239 + PI radiants)
	for (int i = 0; i < fNumPhiSteps; i++)
	{
		//second loop, Theta:
		//start at 0 degrees (0 radiants) and increment to 360 degrees
		//which is 2 * PI radiants
		for (int j = 0; j < fNumThetaSteps; j++)
		{
			//******************************************************************
			//first vertex texture coordinates

			//UV coordinates
			//V
			this->vDomeArray_ptr[iterator+1] = (fPhiMin + i * fSizePhiStep) / (fPI);
			//U
			this->vDomeArray_ptr[iterator] = (fThetaMin + j * fSizeThetaStep) / (2 * fPI) ;
			iterator+=2;
			//first vertex coordinates
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + i * fSizePhiStep)*cos(fThetaMin + j * fSizeThetaStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * cos(fPhiMin + i * fSizePhiStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + i * fSizePhiStep)*sin(fThetaMin + j * fSizeThetaStep);
			iterator++;
			//******************************************************************
			//second vertex texture coordinates

			//UV coordinates
			//V
			this->vDomeArray_ptr[iterator+1] = (fPhiMin + (i+1) * fSizePhiStep) / (fPI);
			//U
			this->vDomeArray_ptr[iterator] = (fThetaMin + j * fSizeThetaStep) / (2 * fPI) ;
			iterator+=2;
			//first vertex coordinates
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + (i+1) * fSizePhiStep)*cos(fThetaMin + j * fSizeThetaStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * cos(fPhiMin + (i+1) * fSizePhiStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + (i+1) * fSizePhiStep)*sin(fThetaMin + j * fSizeThetaStep);
			iterator++;
			//******************************************************************
			//third vertex texture coordinates

			//UV coordinates
			//V
			this->vDomeArray_ptr[iterator+1] = (fPhiMin + i * fSizePhiStep) / (fPI);
			//U
			this->vDomeArray_ptr[iterator] = (fThetaMin + (j+1) * fSizeThetaStep) / (2 * fPI) ;
			iterator+=2;
			//first vertex coordinates
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + i * fSizePhiStep)*cos(fThetaMin + (j+1) * fSizeThetaStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * cos(fPhiMin + i * fSizePhiStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + i * fSizePhiStep)*sin(fThetaMin + (j+1) * fSizeThetaStep);
			iterator++;
			//******************************************************************
			//fourth vertex texture coordinates

			//UV coordinates
			//V
			this->vDomeArray_ptr[iterator+1] = (fPhiMin + (i+1) * fSizePhiStep) / (fPI);
			//U
			this->vDomeArray_ptr[iterator] = (fThetaMin + (j+1) * fSizeThetaStep) / (2 * fPI) ;
			iterator+=2;
			//first vertex coordinates
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + (i+1) * fSizePhiStep)*cos(fThetaMin + (j+1) * fSizeThetaStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * cos(fPhiMin + (i+1) * fSizePhiStep);
			iterator++;
			this->vDomeArray_ptr[iterator] = fR * sin(fPhiMin + (i+1) * fSizePhiStep)*sin(fThetaMin + (j+1) * fSizeThetaStep);
			iterator++;
		}

	}
	return true;
}

bool SkySphere::Render(const TextureSet& textureset_ref, const CAM& c_ref,
					   const SettingsSubSet& sss_ref) const
{
	//bool check
	if (!sss_ref.GetKernelSettings().skysphere) return false;
	//push matrix
	glPushMatrix();
	//load identity
	glLoadIdentity();
	//push attribs
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//ROTATE CAMERA WITHOUT TRANSLATIONS
	gluLookAt( /*c_ref.vSVS[0].fCoords[0]*/0.0f, /*c_ref.vSVS[0].fCoords[1]*/0.0f, /*c_ref.vSVS[0].fCoords[2]*/0.0f,
	c_ref.vSVS[1].fCoords[0]/*+c_ref.vSVS[0].fCoords[0]*/, c_ref.vSVS[1].fCoords[1]/*+c_ref.vSVS[0].fCoords[1]*/, c_ref.vSVS[1].fCoords[2]/*+c_ref.vSVS[0].fCoords[2]*/,
	c_ref.vSVS[2].fCoords[0], c_ref.vSVS[2].fCoords[1], c_ref.vSVS[2].fCoords[2]);
	//bind texture to the skysphere texture
	glBindTexture( GL_TEXTURE_2D, textureset_ref.GetTextureIndices()[1]);
	//enable textures
	glEnable(GL_TEXTURE_2D);
	//disable depth test, since sphere data is always overriden by other data
	glDisable(GL_DEPTH_TEST);
	//change color for hyper factor
	glColor3f(0.9, 0.9, 0.9);
	//setup interleived arrays
	glInterleavedArrays(GL_T2F_V3F,0,this->vDomeArray_ptr);
	//draw arrays
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2592);
	//disable client state
	glDisableClientState(GL_VERTEX_ARRAY);
	//re-enable dept test, since sphere has been drawn
	glEnable(GL_DEPTH_TEST);
	//disable textures
	glDisable(GL_TEXTURE_2D);
	//pop attribs
	glPopAttrib();
	//pop matrix
	glPopMatrix();

	return true;
}




