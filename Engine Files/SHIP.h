////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	SHIP.h
////////////////////////////////////////////////

/*
NOTE:
	main ship class
*/

#ifndef SHIP_H
#define SHIP_H

#include "EE.h"

class SHIP: public EE
{
public:
	//default constructor
	SHIP();
	//copy constructor
	SHIP(const SHIP& s_ref);
	//complex constructor
	SHIP(	/*GE parameters*/int iType, string sName,
			/*DE parameters*/float fMass, float fForce, float fHyper,
							 const VEC* vSVS_ptr, const float* fHVS_ptr,
			/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
			/*VE parameters*/float fHitPoints, bool bIsVulnerable,
			/*EE parameters*/int iModel);

	//destructor
	virtual ~SHIP();

	//overriden methods from DE
	void CalcInputDynamics(const bool* bThrottle);
	void CalcAutoDynamics();
	void ApplyDynamics(float fDt);

};


#endif SHIP_H
