////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	HELI.h
////////////////////////////////////////////////

/*
NOTE:
	This class is a leaf class, and can be instantiated.
	It will be the standard flying entity.
*/

#ifndef HELI_H
#define HELI_H

//includes
#include "SHIP.h"

//static HELI type
const static int HELI_TYPE = 10;
//static HELI name
const static string HELI_NAME = "HELI";
//static HELI mass
const static float HELI_MASS = 500.0f;
//static HELI firce
const static float HELI_FORCE = 500.0f;
//static HELI hyper force
const static float HELI_HYPER = 5000.0f;
//static HELI bounding volume
const static BV HELI_BV(BS(5));
//static static HELI hit points
const static float HELI_HP = 100.0f;
//concrete settings
const static bool HELI_CONCRETE = true;
//vulnerability settings
const static bool HELI_VULNERABLE = true;
//heli model type
const static int HELI_MODEL = 0;

//class declaration
class HELI: public SHIP
{
public:
	//default constructor
	HELI();
	//copy constructor
	HELI(const HELI& heli_ref);
	//complex construction
	HELI(const VEC* vSVS_ptr, const float* fHVS_ptr);
	//destructor
	~HELI();

};


#endif HELI_H