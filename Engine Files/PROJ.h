////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	PROJ.h
////////////////////////////////////////////////

#ifndef PROJ_H
#define PROJ_H

//includes
#include "EE.h"

//class declaration
class PROJ: public EE
{
public:
	//default construction
	PROJ();
	//copy constructor
	PROJ(const PROJ& p_ref);
	//complex construction
	PROJ(	/*GE parameters*/int iType, string sName,
			/*DE parameters*/float fMass, float fForce, float fHyper,
							 const VEC* vSVS_ptr, const float* fHVS_ptr,
			/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
			/*VE parameters*/float fHitPoints, bool bIsVulnerable, int iModel,
			/*member parameters*/float fCollisionDamage, float fSplashFactor, float fSplashRadius);
			
	//destructor
	virtual ~PROJ();

	//collision damage
	float fCollisionDamage;
	//splash factor
	float fSplashFactor;
	//splash radius
	float fSplashRadius;

	//overriden methods from DE
	void CalcInputDynamics(const bool* bThrottle);
	void CalcAutoDynamics();
	void ApplyDynamics(float fDt);

};

#endif PROJ_H