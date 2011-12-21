////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	CAM.h
////////////////////////////////////////////////

/*
NOTE:
	this is the camera class.  It extends the DE class,
	since it is the level which presents the necessary
	values for a camera.
*/

#ifndef CAM_H
#define CAM_H

#include "DE.h"

//camera mass
const static float CAM_MASS = 100.0f;
//camera force
const static float CAM_FORCE = 100.0f;
//camera hyper force
const static float CAM_HYPER = 100.0f;
//camera type
const static int CAM_TYPE = 0;
//camera name
const static string CAM_NAME = "CAMERA";

class CAM: public DE
{
public:
	//default constructor
	CAM();
	//copy constructor
	CAM(const CAM& c_ref);
	//complex construction
	CAM(string sName, const VEC* vSVS_ptr, const float* fHVS_ptr);
	//destructor
	~CAM();

	//glue camera position to parameter target
    void GluePosTo(const DE& de_ref);
	//glue camera angles to parameter target
	void GlueAnglesTo(const DE& de_ref);
	//glue camera position&angles to parameter target
	void GlueAllTo(const DE& de_ref);

	//overriden methods from DE
	void CalcInputDynamics(const bool* bThrottle);
	void CalcAutoDynamics();
	void ApplyDynamics(float fDt);

};

#endif CAM_H