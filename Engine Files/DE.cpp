////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	DE.cpp
////////////////////////////////////////////////

#include "DE.h"

//copy constructor
DE::DE(const DE& de_ref)
:GE(de_ref)
{
	//copy mass
	this->fMass = de_ref.fMass;
	//copy forces
	this->fForce = de_ref.fForce;
	this->fHyper = de_ref.fHyper;
	//copy standardvectorset
	for (int i = 0; i < 5; i++)
		this->vSVS[i] = de_ref.vSVS[i];
	//copy hypervalueset
	for (int i = 0; i < 3; i++)
		this->fHVS[i] = de_ref.fHVS[i];
}

//complex construction
DE::DE(	/*GE parameters*/int iType, string sName,
		/*member parameters*/float fMass, float fForce, float fHyper,
							 const VEC* vSVS_ptr,const float* fHVS_ptr)
:GE(iType, sName)
{
	//assign mass...
	this->fMass = fMass;
	//assign forces
	this->fForce = fForce;
	this->fHyper = fHyper;

	//check if vSVS_ptr parameter is valid
	if (vSVS_ptr)
	{
		//copy standardvectorset
		for (int i = 0; i < 5; i++)
		{
		this->vSVS[i] = vSVS_ptr[i];
		}
	}
	//if null, create a simple standardvectorset
	else
	{
		this->vSVS[0] = VEC(0,0,0,1);
		this->vSVS[1] = VEC(0,0,-1,0);
		this->vSVS[2] = VEC(0,1,0,0);
		this->vSVS[3] = VEC(0,0,0,0);
		this->vSVS[4] = VEC(0,0,0,0);
		
	}
	//check if fHVS_ptr parameter is not null
	if (fHVS_ptr)
	{
	//copy hypervalueset
	for (int i = 0; i < 3; i++)
		this->fHVS[i] = fHVS_ptr[i];
	}
	//if null, reset them all to 0
	else
	{
		this->fHVS[0] = 0;
		this->fHVS[1] = 0;
		this->fHVS[2] = 0;
	}
}

//destructor
DE::~DE()
{

}

//pitch rotation method
void DE::Pitch(float fAngle)
{
	//temp strafe vector
	VEC vStrafe;
	MathManipulations::CroVEC(vStrafe, this->vSVS[2], this->vSVS[1]);
	MathManipulations::NorVEC(vStrafe);
    //rotation of directional vector
	MathManipulations::RotMtx3X3(this->vSVS[1], vStrafe, fAngle);
	//rotation of normal vector
	MathManipulations::RotMtx3X3(this->vSVS[2], vStrafe, fAngle);
}

//yaw rotation method
void DE::Yaw(float fAngle)
{
	//perform rotations
	MathManipulations::RotMtx3X3(this->vSVS[1], this->vSVS[2], fAngle);
}

//roll rotation method
void DE::Roll(float fAngle)
{
	//perform rotations
	MathManipulations::RotMtx3X3(this->vSVS[2], this->vSVS[1], fAngle);
}

//copy standardvectorset
void DE::CopySVS(const VEC* vSVS_ptr)
{
	for (int i = 0; i < 5; i++)
		this->vSVS[i] = vSVS_ptr[i];
}

//copy hypervalueset
void DE::CopyHVS(const float* fHVS_ptr)
{
	for (int i = 0; i < 3; i++)
		this->fHVS[i] = fHVS_ptr[i];
}
