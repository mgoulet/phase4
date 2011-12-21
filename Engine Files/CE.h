////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	CE.h
////////////////////////////////////////////////

/*
NOTE:
	This class inherits from the DE class, and adds
	collision capabilities
*/

#ifndef CE_H
#define CE_H

//includes
#include "DE.h"
#include "EngineVolumes.h"

//class definition
class CE: public DE
{

public:

	//copy construction
	CE(const CE& ce_ref);
	//complex construction
	CE(	/*GE parameters*/int iType, string sName,
		/*DE parameters*/float fMass, float fForce, float fHyper,
						 const VEC* vSVS_ptr, const float* fHVS_ptr,
		/*member parameters*/const BV* bv_ptr, bool bIsConcrete);

		//destructor
	virtual ~CE();

	//abstract bounding volume
	const BV* bv_ptr;

	//is concrete
	bool bIsConcrete;

	//first collision test (BS)
	bool SphericalCollisionTest(const CE& ce_ref) const;

	//is colliding bool
	bool bIsColliding;

};


#endif CE_H