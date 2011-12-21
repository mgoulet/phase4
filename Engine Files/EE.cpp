////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	EE.cpp
////////////////////////////////////////////////

#include "EE.h"

EE::EE(const EE& ee_ref)
:VE(ee_ref)
{
	//copy model indice
	this->iModel = ee_ref.iModel;
}

EE::EE(	/*GE parameters*/int iType, string sName,
		/*DE parameters*/float fMass, float fForce, float fHyper,
						 const VEC* vSVS_ptr, const float* fHVS_ptr,
		/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
		/*VE parameters*/float fHitPoints, bool bIsVulnerable,
		/*member parameters*/int iModel)
:VE(iType, sName, fMass, fForce, fHyper, vSVS_ptr, fHVS_ptr, bv_ptr, bIsConcrete, fHitPoints, bIsVulnerable)
{
	//set model indice
	this->iModel = iModel;
}

EE::~EE()
{
	//empty
}

