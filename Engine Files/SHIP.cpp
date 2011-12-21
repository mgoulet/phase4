////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	SHIP.cpp
////////////////////////////////////////////////

#include "SHIP.h"

//coy constructor
SHIP::SHIP(const SHIP& s_ref):EE(s_ref)
{
	//empty for now
}

//complex construction
SHIP::SHIP(	/*GE parameters*/int iType, string sName,
			/*DE parameters*/float fMass, float fForce, float fHyper,
							 const VEC* vSVS_ptr, const float* fHVS_ptr,
			/*CE parameters*/const BV* bv_ptr, bool bIsConcrete,
			/*VE parameters*/float fHitPoints, bool bIsVulnerable,
			/*EE parameters*/int iModel)
			/*call to parent*/:EE(iType, sName, fMass, fForce, fHyper, vSVS_ptr, fHVS_ptr, bv_ptr, bIsConcrete, fHitPoints, bIsVulnerable, iModel)
{
	//empty
}

//destructor
SHIP::~SHIP()
{
	//empty
}

void SHIP::CalcInputDynamics(const bool* bThrottleSet_ptr)
{
	//////////////////////////////////////////
	//compute 3d dynamics
	//////////////////////////////////////////
	//reset acceleration
	this->vSVS[4] = VEC(0.0f,0.0f,0.0f,0.0f);
	//directional throttle
	if (bThrottleSet_ptr[0]) {MathManipulations::AddVEC(this->vSVS[4], this->vSVS[1]);}
	if (bThrottleSet_ptr[1]) {MathManipulations::SubVEC(this->vSVS[4], this->vSVS[1]);}
	//vertical throttle
	if (bThrottleSet_ptr[2]) {MathManipulations::AddVEC(this->vSVS[4], this->vSVS[2]);}
	if (bThrottleSet_ptr[3]) {MathManipulations::SubVEC(this->vSVS[4], this->vSVS[2]);}
	//make vector that represents sidestepping
	VEC vSide;
	MathManipulations::CroVEC(vSide, this->vSVS[2], this->vSVS[1]);
	//sidestep throttles
	if (bThrottleSet_ptr[4]) {MathManipulations::AddVEC(this->vSVS[4], vSide);}
	if (bThrottleSet_ptr[5]) {MathManipulations::SubVEC(this->vSVS[4], vSide);}

	//normalize total resulting acceleration vector (into a simple direction)
	MathManipulations::NorVEC(this->vSVS[4]);
	//compute proper force/mass ratio
	float fResultingAccelerationFactor = this->fForce / this->fMass;
	//scale the acceleration vector
	MathManipulations::MulVEC(this->vSVS[4], fResultingAccelerationFactor);

	//////////////////////////////////////////
	//compute hyperdynamics
	//////////////////////////////////////////
	//reset hyper throttle
	this->fHVS[2] = 0.0f;
	//compute throttle
	if (bThrottleSet_ptr[6]) {this->fHVS[2] += this->fHyper / this->fMass;}
	if (bThrottleSet_ptr[7]) {this->fHVS[2] -= this->fHyper / this->fMass;}
}

void SHIP::CalcAutoDynamics()
{
}

void SHIP::ApplyDynamics(float fDt)
{
	//precision counter guard
	if (fDt >= 10) {return;}
	if (fDt <= -10) {return;}

	//////////////////////////////////////////
	//apply 3d dynamics
	//////////////////////////////////////////

	//Displacement changes
	//D = Di + Vit + (1/2)At^2
	VEC Vadditive = this->vSVS[3];							// Vi
	MathManipulations::MulVEC(Vadditive,fDt);				// Vit
	VEC Aadditive = this->vSVS[4];							// A
	MathManipulations::MulVEC(Aadditive, (fDt*fDt));		// (1/2)At^2
	MathManipulations::MulVEC(Aadditive, 0.5);				// (1/2)At^2
	//apply displacement changes
	MathManipulations::AddVEC(this->vSVS[0], Vadditive);	// D = Di + Vit
	MathManipulations::AddVEC(this->vSVS[0], Aadditive);	// + (1/2)At^2

	//velocity changes
	//V = (Vi + At) * (1 - AIR_FRICTION*fDt)
	Aadditive = this->vSVS[4];	
	MathManipulations::MulVEC(Vadditive,fDt);				// At
	//apply velocity changes
	MathManipulations::AddVEC(this->vSVS[3], Aadditive);	// V = Vi + At
	//add friction
	MathManipulations::MulVEC(this->vSVS[3], (1 - AIR_FRICTION * fDt));

	//acceleration changes
	// A = 0 (reset value; up to next frame to decide if  value is set)
	this->vSVS[4] = VEC(0.0f,0.0f,0.0f,0.0f);

	//////////////////////////////////////////
	//apply hyperdynamics
	//////////////////////////////////////////
	//displacement changes
	//D = Di + Vit + (1/2)At^2
	this->fHVS[0] += (this->fHVS[1]*fDt) + (1/2)*this->fHVS[2]*(fDt*fDt);
	//velocity changes
	//V = (Vi + At)
	this->fHVS[1] += this->fHVS[2] * fDt;
	//multiply friction factor
	this->fHVS[1] -= (this->fHVS[1] * (HYPER_FRICTION * fDt));
	//  A = 0 (reset value; up to next frame to decide if  value is set)
	this->fHVS[2] = 0.0f;
	//360 degrees value bounds check
	if (this->fHVS[0] <= 0  ) {this->fHVS[0] = 360 - abs(this->fHVS[0]);}
	if (this->fHVS[0] >= 360) {this->fHVS[0] -= 360;}
	

}



