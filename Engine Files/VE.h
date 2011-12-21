////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	VE.h
////////////////////////////////////////////////

/*
NOTE:
	This class is the parent of all vulnerable entities.
*/

#ifndef VE_H
#define VE_H

//includes
#include "CE.h"

class VE: public CE
{

public:

	//copy constructor
	VE(const VE& ve_ref);
	//parameterized construction
	VE(	/*GE parameters*/int iType, string sName,
		/*DE parameters*/float fMass, float fForce, float fHyper,
						 const VEC* vSVS_ptr, const float* fHVS_ptr,
		/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
		/*member parameters*/float fHitPoints, bool bIsVulnerable);

	//destructor
	virtual ~VE();

	//hit points
	float fHitPoints;
	//vulnerability bool
	bool bIsVulnerable;


};



#endif VE_H