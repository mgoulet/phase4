////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	HELI.cpp
////////////////////////////////////////////////

#include "HELI.h"

//default constructor
HELI::HELI()
:SHIP(	/*GE parameters*/HELI_TYPE, HELI_NAME,
		/*DE parameters*/HELI_MASS, HELI_FORCE, HELI_HYPER,
						 0, 0,
		/*CE parameters*/&HELI_BV, HELI_CONCRETE,
		/*VE parameters*/HELI_HP, HELI_VULNERABLE,
		/*EE parameters*/
		/*SHIP parameters*/HELI_MODEL)
{
	//empty
}

//copy constructor
HELI::HELI(const HELI& heli_ref)
:SHIP(heli_ref)
{
	//empty
}

//complex construction
HELI::HELI(	const VEC* vSVS_ptr, const float* fHVS_ptr)
:SHIP(	/*GE parameters*/HELI_TYPE, HELI_NAME,
		/*DE parameters*/HELI_MASS, HELI_FORCE, HELI_HYPER,
						 vSVS_ptr, fHVS_ptr,
		/*CE parameters*/&HELI_BV, HELI_CONCRETE,
		/*VE parameters*/HELI_HP, HELI_VULNERABLE,
		/*EE parameters*/
		/*SHIP parameters*/HELI_MODEL)
{
	//empty
}

HELI::~HELI()
{
	//empty
}
