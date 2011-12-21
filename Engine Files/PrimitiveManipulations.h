////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	PrimitiveManipulations.h
////////////////////////////////////////////////

/*
NOTE: This namespace will contain the different
polygon related entities that will be rendered
by the GPU.  Such entities consist of TRI and 
TRISTRIP.
*/

#ifndef PRIMITIVEMANIPUALTIONS_H
#define PRIMITIVEMANIPUALTIONS_H

#include <deque>
#include "FundamentalManipulations.h"
#include "TRI.h"
#include "TRISTRIP.h"

using namespace FundamentalManipulations;

namespace PrimitiveManipulations
{
/////////////////////////////////////////////
//EXTERNAL METHODS DEFINITIONS
/////////////////////////////////////////////

	void ExternPrint(const TRI& t_ref);
	void ExternPrint(const TRISTRIP& ts_ref);

	bool  ExternSplitTri	   (std::deque<TRI>& dptPosList_ref, 
								std::deque<TRI>& dptOnList_ref,
								std::deque<TRI>& dptNegList_ref,
								const TRI& t_ref, const PLANE& p_ref);
	bool  ExternCalcBarycentric	(VEC3& vTarget_ref, 
								const TWINVEC3& tv_ref, 
								const TRI& t_ref);
};


#endif PRIMITIVEMANIPUALTIONS_H