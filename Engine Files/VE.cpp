////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	VE.cpp
////////////////////////////////////////////////

#include "VE.h"

//copy constructor
VE::VE(const VE& ve_ref)
:CE(ve_ref)
{
	this->fHitPoints = ve_ref.fHitPoints;
	this->bIsVulnerable = ve_ref.bIsVulnerable;
}

//complex construction
VE::VE(	/*GE parameters*/int iType, string sName,
		/*DE parameters*/float fMass, float fForce, float fHyper,
						 const VEC* vSVS_ptr, const float* fHVS_ptr,
		/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
		/*member parameters*/float fHitPoints, bool bIsVulnerable)
:CE(iType, sName, fMass, fForce, fHyper, vSVS_ptr, fHVS_ptr, bv_ptr, bIsConcrete)
{
	//assign hit points
	this->fHitPoints = fHitPoints;
	//assign vulnerability
	this->bIsVulnerable = bIsVulnerable;
}

//destructor
VE::~VE()
{
	//empty
}