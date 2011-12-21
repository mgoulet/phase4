////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	CE.cpp
////////////////////////////////////////////////

#include "CE.h"

//copy constructor
CE::CE(const CE& ce_ref)
:DE(ce_ref)
{
	//deep copy of bounding volume
	this->bv_ptr = ce_ref.bv_ptr;
	//set concrete
	this->bIsConcrete = ce_ref.bIsConcrete;
	//set collision bool
	this->bIsColliding = false;
}

//complex construction
CE::CE(	/*GE parameters*/int iType, string sName,
		/*DE parameters*/float fMass, float fForce, float fHyper, 
						 const VEC* vSVS_ptr, const float* fHVS_ptr,
		/*member parameters*/const BV* bv_ptr, bool bIsConcrete)
:DE(iType, sName, fMass, fForce, fHyper, vSVS_ptr, fHVS_ptr)
{
	//deep copy of bounding volume
	this->bv_ptr = bv_ptr;
	//set concrete value
	this->bIsConcrete = bIsConcrete;
	//set collision bool
	this->bIsColliding = false;
}

//destructor
CE::~CE()
{
	//empty
}

//first degree collision
bool CE::SphericalCollisionTest(const CE& ce_ref) const
{
	//no collision if the entity is not concrete
	if (!this->bIsConcrete) return false;

	//check for collision between spheres
	VEC  vBetween = ce_ref.vSVS[0];
	MathManipulations::SubVEC(vBetween, this->vSVS[0]);
	float fDistance = MathManipulations::SizVEC(vBetween);
	if (fDistance <= this->bv_ptr->bSphere.fRadius + ce_ref.bv_ptr->bSphere.fRadius)
	{
		return true;
	}
	//if above check failed, then return false.
	return false;
}



