////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	ROCKET.cpp
////////////////////////////////////////////////

#include "ROCKET.h"

//default constructor
ROCKET::ROCKET()
:PROJ(	/*GE parameters*/ROCKET_TYPE, ROCKET_NAME,
		/*DE parameters*/ROCKET_MASS, ROCKET_FORCE, ROCKET_HYPER,
						 0, 0,
		/*CE parameters*/&ROCKET_BV, ROCKET_CONCRETE,
		/*VE parameters*/ROCKET_HP, ROCKET_VULNERABLE,
		/*EE parameters*/ROCKET_MODEL,
		/*PROJ parameters*/ROCKET_COLLISIONDAMAGE, ROCKET_SPLASHFACTOR, ROCKET_SPLASHRADIUS)
{
	//empty
}

//copy constructor
ROCKET::ROCKET(const ROCKET& r_ref)
:PROJ(r_ref)
{
	//empty
}

//complex constructor
ROCKET::ROCKET(const VEC* vSVS_ptr, const float* fHVS_ptr)
:PROJ(	/*GE parameters*/ROCKET_TYPE, ROCKET_NAME,
		/*DE parameters*/ROCKET_MASS, ROCKET_FORCE, ROCKET_HYPER,
						 vSVS_ptr, fHVS_ptr,
		/*CE parameters*/&ROCKET_BV, ROCKET_CONCRETE,
		/*VE parameters*/ROCKET_HP, ROCKET_VULNERABLE,
		/*EE parameters*/ROCKET_MODEL,
		/*PROJE parameters*/ROCKET_COLLISIONDAMAGE, ROCKET_SPLASHFACTOR, ROCKET_SPLASHRADIUS)
{
	//empty
}

//destructor
ROCKET::~ROCKET()
{
	//empty
}