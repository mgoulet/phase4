////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	CAM.cpp
////////////////////////////////////////////////

#include "CAM.h"

//default constructor
CAM::CAM()
:DE(CAM_TYPE, CAM_NAME, CAM_MASS, CAM_FORCE, CAM_HYPER, 0, 0)
{
	//empty
}

//copy constructor
CAM::CAM(const CAM& c_ref)
:DE(c_ref)
{
	//empty
}

//complex construction
CAM::CAM(string sName, const VEC* vSVS_ptr, const float* fHVS_ptr)
:DE(/*GE parameters*/CAM_TYPE, sName,
	/*DE parameters*/CAM_MASS, CAM_FORCE, CAM_HYPER,
					 vSVS_ptr, fHVS_ptr)
{
	//empty
}

//destructor
CAM::~CAM()
{
	//empty
}

void CAM::GluePosTo(const DE& de_ref)
{
	//copying position explicitly
	this->vSVS[0] = de_ref.vSVS[0];
}

void CAM::GlueAnglesTo(const DE& de_ref)
{
	//copying angles explicitly
	for (int i = 1; i < 3; i++)
		this->vSVS[i] = de_ref.vSVS[i];
}

void CAM::GlueAllTo(const DE& de_ref)
{
	for (int i = 0; i < 5; i++)
		this->vSVS[i] = de_ref.vSVS[i];
	for (int i = 0; i < 3; i++)
		this->fHVS[i] = de_ref.fHVS[i];
}

void CAM::CalcInputDynamics(const bool* bThrottleSet_ptr)
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

void CAM::CalcAutoDynamics()
{
	//nothign happens when control target is a camera.
}

void CAM::ApplyDynamics(float fDt)
{
	//////////////////////////////////////////
	//apply 3d dynamics
	//////////////////////////////////////////
	//apply velocity to position
	//get additive velocity
	VEC vAdditiveVelocity = this->vSVS[3];
	//scale it to proper time frame
//	MathManipulations::MulVEC(vAdditiveVelocity,fDt);
	//add to position
	MathManipulations::AddVEC(this->vSVS[0], vAdditiveVelocity);
	//apply acceleration to velocity
	//get additive acceleration
	VEC vAdditiveAcceleration = this->vSVS[4];
	//scale it to proper time frame
	MathManipulations::MulVEC(vAdditiveAcceleration, fDt);
	//add to velocity
	MathManipulations::AddVEC(this->vSVS[3], vAdditiveAcceleration);
	//apply friction
	MathManipulations::MulVEC(this->vSVS[3], (1 - AIR_FRICTION));

	//reset acceleration if it is a ship
	this->vSVS[4] = VEC(0.0f,0.0f,0.0f,0.0f);

	//////////////////////////////////////////
	//apply hyperdynamics
	//////////////////////////////////////////
	//apply hyper velocity to hyperposition
	this->fHVS[0] += this->fHVS[1]/* * fDt*/;
	//apply hyper accel to hyper velocity
	this->fHVS[1] += this->fHVS[2] * fDt;
	//apply hyper friction
	this->fHVS[1] *= (1 - HYPER_FRICTION);
	//reset hyper throttle
	this->fHVS[2] = 0.0f;
}