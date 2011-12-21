////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	FundamentalManipulations.h
////////////////////////////////////////////////

/*
NOTE: This file contains all the complex
manipulations between the low level mathematical
entities contained in the ComputationalSpace folder.
Including this file includes the headers of all
it's required subcomponents.
*/

#ifndef FUNDAMENTALMANIPULATIONS_H
#define FUNDAMENTALMANIPULATIONS_H

#include <iostream>
#include <cmath>
#include "VEC3.h"
#include "TWINVEC3.h"
#include "PLANE.h"

using namespace std;

namespace FundamentalManipulations
{

/////////////////////////////////////////////
//EXTERNAL METHODS DEFINITIONS
/////////////////////////////////////////////

	void ExternPrint(const VEC3& v_ref);
	void ExternPrint(const TWINVEC3& tv_ref);
	void ExternPrint(const PLANE& p_ref);

	bool  ExternLinIntersect(VEC3& v_ref, const TWINVEC3& tv_ref, const PLANE& p_ref);
	bool  ExternRayIntersect(VEC3& v_ref, const TWINVEC3& tv_ref, const PLANE& p_ref);
	bool  ExternSegIntersect(VEC3& v_ref, const TWINVEC3& tv_ref, const PLANE& p_ref);
	bool  ExternMatrixRotation(VEC3& vTarget_ref, const VEC3& vAxis_ref, float fAngle);
	int	  ExternPlanarTristate(const VEC3& v_ref, const PLANE& p_ref, float fError); 
	float ExternDistanceFromPlane(const VEC3& v_ref, const PLANE& p_ref);

};

#endif FUNDAMENTALMANIPULATIONS_H
