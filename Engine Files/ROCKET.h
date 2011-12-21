////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	ROCKET.h
////////////////////////////////////////////////

/*
NOTE:
	This is an instantiable class, representing
	rockets.
*/


#ifndef ROCKET_H
#define ROCKET_H

//includes
#include "PROJ.h"

//static ROCKET type
const static int ROCKET_TYPE = 20;
//static ROCKET name
const static string ROCKET_NAME = "ROCKET";
//static ROCKET mass
const static float ROCKET_MASS = 50.0f;
//static ROCKET force
const static float ROCKET_FORCE = 100.0f;
//static ROCKET hyper force
const static float ROCKET_HYPER = 100.0f;
//static ROCKET bounding volume
const static BV ROCKET_BV(BS(5));
//static static ROCKET hit points
const static int ROCKET_HP = 10;
//concrete settings
const static bool ROCKET_CONCRETE = true;
//vulnerability settings
const static bool ROCKET_VULNERABLE = true;
//ROCKET model type
const static int ROCKET_MODEL = 1;
//ROCKET collision damage
const static float ROCKET_COLLISIONDAMAGE = 50.0f;
//ROCKET splash factor
const static float ROCKET_SPLASHFACTOR = 0.5f;
//ROCKET splash radius
const static float ROCKET_SPLASHRADIUS = 100.0f;


//class definition
class ROCKET: public PROJ
{
public:

	//default constructor
	ROCKET();
	//copy constructor
	ROCKET(const ROCKET& r_ref);
	//complex construction
	ROCKET(	const VEC* vSVS_ptr, const float* fHVS_ptr);
	//destructor
	~ROCKET();

};

#endif ROCKET_H