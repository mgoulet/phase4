////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	PROJ.cpp
////////////////////////////////////////////////

#include "PROJ.h"

//copy constructor
PROJ::PROJ(const PROJ& p_ref)
:EE(p_ref)
{
	//copy members
	this->fCollisionDamage = p_ref.fCollisionDamage;
	this->fSplashFactor = p_ref.fSplashFactor;
	this->fSplashRadius = p_ref.fSplashRadius;
}

//complex constructor
PROJ::PROJ(	/*GE parameters*/int iType, string sName,
			/*DE parameters*/float fMass, float fForce, float fHyper,
							 const VEC* vSVS_ptr, const float* fHVS_ptr,
			/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
			/*VE parameters*/float fHitPoints, bool bIsVulnerable,
			/*EE parameters*/int iModel,
			/*member parameters*/float fCollisionDamage, float fSplashFactor, float fSplashRadius)
:EE(	/*GE parameters*/iType, sName,
		/*DE parameters*/fMass, fForce, fHyper,
						 vSVS_ptr, fHVS_ptr,
		/*CE parameters*/bv_ptr, bIsConcrete,
		/*VE parameters*/fHitPoints, bIsVulnerable,
		/*EE parameters*/iModel)
{
	//copy members
	this->fCollisionDamage = fCollisionDamage;
	this->fSplashFactor = fSplashFactor;
	this->fSplashRadius = fSplashRadius;
}

//destructor
PROJ::~PROJ()
{
	//empty
}

void PROJ::CalcInputDynamics(const bool* bThrottleSet_ptr)
{
	//set accel to direction
	this->vSVS[4] = this->vSVS[1];
	//normalize total resulting acceleration vector (into a simple direction)
	MathManipulations::NorVEC(this->vSVS[4]);
	//multiply by the proper accel factor
	MathManipulations::MulVEC(this->vSVS[4], this->fForce / this->fMass);
}

void PROJ::CalcAutoDynamics()
{
	//////////////////////////////////////////
	//compute 3d dynamics
	//////////////////////////////////////////
	//set accel to direction
	this->vSVS[4] = this->vSVS[1];
	//normalize total resulting acceleration vector (into a simple direction)
	MathManipulations::NorVEC(this->vSVS[4]);
	//multiply by the proper accel factor
	MathManipulations::MulVEC(this->vSVS[4], this->fForce / this->fMass);

	//////////////////////////////////////////
	//compute hyperdynamics
	//////////////////////////////////////////
	//reset hyper throttle, unapplicable for rockets for the time being
	this->fHVS[2] = 0.0f;
}

void PROJ::ApplyDynamics(float fDt)
{
	//////////////////////////////////////////
	//apply 3d dynamics
	//////////////////////////////////////////
	//Displacement changes
	//D = Di + Vit + (1/2)At^2
	VEC Vadditive = this->vSVS[3];							// Vi
	MathManipulations::MulVEC(Vadditive,fDt);				// Vit
	VEC Aadditive = this->vSVS[4];							// A
	MathManipulations::MulVEC(Aadditive, (fDt*fDt)/2);		// (1/2)At^2
	//apply displacement changes
	MathManipulations::AddVEC(this->vSVS[0], Vadditive);	// D = Di + Vit
	MathManipulations::AddVEC(this->vSVS[0], Aadditive);	// + (1/2)At^2

	//velocity changes
	//V = (Vi + At) * (1 - AIR_FRICTION*fDt)
	Aadditive = this->vSVS[4];								// A
	MathManipulations::MulVEC(Vadditive,fDt);				// At
	//apply velocity changes
	MathManipulations::AddVEC(this->vSVS[3], Aadditive);	// V = Vi + At
	//add friction
	MathManipulations::MulVEC(this->vSVS[3], (1 - AIR_FRICTION*fDt));

	//acceleration changes
	// A = 0 (reset value; up to next frame to decide if  value is set)
	this->vSVS[4] = VEC(0.0f,0.0f,0.0f,0.0f);

	//////////////////////////////////////////
	//apply hyperdynamics
	//////////////////////////////////////////
	//displacement changes
	//D = Di + Vit + (1/2)At^2
	this->fHVS[0] += (this->fHVS[1]*fDt)* (1/2)*this->fHVS[2]*(fDt*fDt);
	//velocity changes
	//V = (Vi + At) * (1 - AIR_FRICTION*fDt)
	this->fHVS[1] += this->fHVS[2] * fDt * (1 - HYPER_FRICTION*fDt);
	//  A = 0 (reset value; up to next frame to decide if  value is set)
	this->fHVS[2] = 0.0f;
}



