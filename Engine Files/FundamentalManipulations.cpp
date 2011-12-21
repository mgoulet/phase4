////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	FundamentalManipulations.cpp
////////////////////////////////////////////////

#include "FundamentalManipulations.h"
using namespace FundamentalManipulations;

////////////////////////////////////////////////
void FundamentalManipulations::ExternPrint(const VEC3& v_ref)
{
	cout << "VEC3(" 
		 << v_ref.ReturnPos(0) << ", "
		 << v_ref.ReturnPos(1) << ", "
		 << v_ref.ReturnPos(2) << ")\n";
}

////////////////////////////////////////////////
bool FundamentalManipulations::ExternLinIntersect(VEC3& v_ref, const TWINVEC3& tv_ref, const PLANE& p_ref)
{
	//parallelism check
	float fNdotV = p_ref.ReturnNorRef().ReturnDot(tv_ref.ReturnDif());
	//if fNdotV == 0, intersection is indefinite
	//ray is parallel to plane, wether on the plane or not.
	if ( (fNdotV > -0.005) && (fNdotV < 0.005) )
	{
		//ERROR, VEC3 is parallel with plane, return false
		//NOTE: will modify parallelism check to accomodate error margin,
		//which will be defined in a namespace somewhere.. :P

		//return false (intersection failure)
		return false;
	}
	else
	{
        //calculate value of t to find intersection
		// t = N.S / N.V
		//N.V = already calculated, finding N.S
		float fNdotS = p_ref.ReturnNorRef().ReturnDot(tv_ref.ReturnRef(0));
		float t = (-1)*(fNdotS + p_ref.ReturnDot()) / fNdotV;
		//assign resulting VEC3 to the directional VEC3 component of the ray 
		v_ref.InternCpy(tv_ref.ReturnDif());
		//multiply that VEC3 with the value of t
		v_ref.InternMul(t);
		//add the static component of the ray
		v_ref.InternAdd(tv_ref.ReturnRef(0));
		//return true (success)
		return true;
	}

}
////////////////////////////////////////////////
bool FundamentalManipulations::ExternRayIntersect(VEC3& v_ref, const TWINVEC3& tv_ref, const PLANE& p_ref)
{
	VEC3 vIntersection;
	if (ExternLinIntersect(vIntersection, tv_ref, p_ref))
	{
		//computation of t value
		float t = vIntersection.ReturnPos(0) - tv_ref.ReturnRef(0).ReturnPos(0);
		t = t / (tv_ref.ReturnRef(1).ReturnPos(0) - tv_ref.ReturnRef(0).ReturnPos(0));
		//check if t value is between bounds
		if ( t >= 0 )
		{
			return true;
		}
	}
	else
	{
		//tv_ref is parallel to p_ref.
		return false;
	}
	//if code segment reaches this, then there is no RAY intersection.
	return false;
}
////////////////////////////////////////////////
bool FundamentalManipulations::ExternSegIntersect(VEC3& v_ref, const TWINVEC3& tv_ref, const PLANE& p_ref)
{
	VEC3 vIntersection;
	if (ExternLinIntersect(vIntersection, tv_ref, p_ref))
	{
		//computation of t value
		float t = vIntersection.ReturnPos(0) - tv_ref.ReturnRef(0).ReturnPos(0);
		t = t / (tv_ref.ReturnRef(1).ReturnPos(0) - tv_ref.ReturnRef(0).ReturnPos(0));
		//check if t value is between bounds
		if ( (t >= 0) || (t <= 1) )
		{
			return true;
		}
	}
	else
	{
		//tv_ref is parallel to p_ref.
		return false;
	}
	//if code segment reaches this, then there is no RAY intersection.
	return false;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
bool FundamentalManipulations::ExternMatrixRotation(VEC3& vTarget_ref, const VEC3& vAxis_ref, float fAngle)
{
	//check to see if rotation axis VEC3 is normalized; if not, error
	if ( (vAxis_ref.ReturnSiz() < 0.99) || (vAxis_ref.ReturnSiz() > 1.01) )
	{
		return false;
	}

	//COS and SIN calculations
	float fCos = cos(fAngle);
	float fSin = sin(fAngle);

	//calculation of the nine matrix positions
	//first row
	float fPos11 = fCos + (1-fCos)*pow(vAxis_ref.ReturnPos(0),2);
	float fPos12 = ((1-fCos)*vAxis_ref.ReturnPos(0)*vAxis_ref.ReturnPos(1)) - fSin*vAxis_ref.ReturnPos(2);
	float fPos13 = ((1-fCos)*vAxis_ref.ReturnPos(0)*vAxis_ref.ReturnPos(2)) + fSin*vAxis_ref.ReturnPos(1);
	//second row
	float fPos21 = ((1-fCos)*vAxis_ref.ReturnPos(0)*vAxis_ref.ReturnPos(1)) + fSin*vAxis_ref.ReturnPos(2);
	float fPos22 = fCos + (1-fCos)*pow(vAxis_ref.ReturnPos(1),2);
	float fPos23 = ((1-fCos)*vAxis_ref.ReturnPos(1)*vAxis_ref.ReturnPos(2)) - fSin*vAxis_ref.ReturnPos(0);
	//third row
	float fPos31 = ((1-fCos)*vAxis_ref.ReturnPos(0)*vAxis_ref.ReturnPos(2)) - fSin*vAxis_ref.ReturnPos(1);
	float fPos32 = ((1-fCos)*vAxis_ref.ReturnPos(1)*vAxis_ref.ReturnPos(2)) + fSin*vAxis_ref.ReturnPos(0);
	float fPos33 = fCos + (1-fCos)*pow(vAxis_ref.ReturnPos(2),2);

	//storing old VEC3 values for computation
	float fOldX = vTarget_ref.ReturnPos(0);
	float fOldY = vTarget_ref.ReturnPos(1);
	float fOldZ = vTarget_ref.ReturnPos(2);

	//assigning actual rotation to target VEC3
	vTarget_ref.InternSet(0, fPos11*fOldX + fPos12*fOldY + fPos13*fOldZ);
	vTarget_ref.InternSet(1, fPos21*fOldX + fPos22*fOldY + fPos23*fOldZ);
	vTarget_ref.InternSet(2, fPos31*fOldX + fPos32*fOldY + fPos33*fOldZ);

	//temp return true
	return true;
}

////////////////////////////////////////////////
int FundamentalManipulations::ExternPlanarTristate(const VEC3& v_ref, const PLANE& p_ref, float fError)
{
	float fDistance = ExternDistanceFromPlane(v_ref, p_ref);
	//round off to zero inside error margin (on plane)
	if ( (fDistance < fError) && (fDistance > (-1)*fError) )
		return 0;
	//behind plane
	if (fDistance > fError)
		return 1;
	//in front of plane
	if (fDistance < (-1)*fError)
		return -1;
	//ERROR
	cout << "TRISTATE ASSERTION FAILURE\n";
	return -1000;
}

////////////////////////////////////////////////
float FundamentalManipulations::ExternDistanceFromPlane(const VEC3& v_ref, const PLANE& p_ref)
{
	return (p_ref.ReturnNorRef().ReturnDot(v_ref) - p_ref.ReturnDot());
}
////////////////////////////////////////////////