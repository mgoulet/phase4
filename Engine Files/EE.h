////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	EE.h
////////////////////////////////////////////////

/*
NOTE:
	This class is the standard class for all
	entities to derive from, if they are to be
	manipulated.
*/

#ifndef EE_H
#define EE_H

//includes
#include "VE.h"


class EE: public VE
{
public:

	//copy constructor
	EE(const EE& ee_ref);
	//complex construction
	EE(	/*GE parameters*/int iType, string sName,
		/*DE parameters*/float fMass, float fForce, float fHyper,
						 const VEC* vSVS_ptr, const float* fHVS_ptr,
		/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
		/*VE parameters*/float fHitPoints, bool bIsVulnerable,
		/*member parameters*/int iModel);

	//destructor
	virtual ~EE();

	//model type
	int iModel;
};


#endif EE_H