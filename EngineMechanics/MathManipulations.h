////////////////////////////////////////////////
//	Martin Goulet
//	Project:
//	MathManipulations.h
////////////////////////////////////////////////

/*
NOTE:	This namespace does NOT contain the manipulations found
		in the PrimitiveManipulations from the previous version
		of the project.
*/

#ifndef MATHMANIPULATIONS_H
#define MATHMANIPULATIONS_H

#include <iostream>
#include <deque>
#include <cmath>
#include "MathEntities.h"
using namespace std;

namespace MathManipulations
{
	//explicit vectorial operator overloaders
	bool	AddVEC		(VEC& vtarget_ref, const VEC& v_ref);
	bool	AddVEC		(VEC& vtarget_ref, const VEC& v1_ref, const VEC& v2_ref);
	bool	SubVEC		(VEC& vtarget_ref, const VEC& v1_ref);
	bool	SubVEC		(VEC& vtarget_ref, const VEC& v1_ref, const VEC& v2_ref);
	bool	MulVEC		(VEC& vtarget_ref, float f);

	//trivial structure manipulations
	float	SizVEC		(const VEC& v_ref);
	bool	InvVEC		(VEC& v_ref);
	bool	NorVEC		(VEC& v_ref);
	bool	CroVEC		(VEC& vtarget_ref, const VEC& v1_ref, const VEC& v2_ref);
	float	DotVEC		(const VEC& v1_ref, const VEC& v2_ref);
	float	RtsCHK		(float fCentreBit, float fErrorBit, float fResultToClassify);
	float	FndDeg		(const VEC& v1_ref, const VEC& v2_ref);
	//compound structure manipulations
	bool	PrlCHK		(const PLN& pln_ref, const TRI& tri_ref);
	bool	IntLINPLN	(VEC& v_ref, const LIN& lin_ref, const PLN& pln_ref);
	bool	IntSEGPLN	(VEC& v_ref, const LIN& lin_ref, const PLN& pln_ref);
	bool	IntRAYPLN	(VEC& v_ref, const LIN& lin_ref, const PLN& pln_ref);

	//3X3 matrix manipulations
	float	DetMtx3X3	(const M3X3& m3x3_ref);
	bool	RotMtx3X3	(VEC& vtarget_ref, const VEC& vxis_ref, float fAngle);
	bool	MulMtx3X3	(M3X3& m3x3_ref, float f);
	bool	MulMtx3X3	(M3X3& m3x3target_ref, const M3X3& m3x3_ref);
	bool	TrsMtx3X3	(M3X3& m3x3_ref);
	bool	InvMtx3X3	(M3X3& m3x3_ref);
	//4X4 matrix manipulations
	bool	CpyMtx4X4	(M4X4& m4x4_ref, const M3X3& m3x3_ref);
	bool	MulMtx4X4	(M4X4& m4x4_ref, float f);
	bool	MulMtx4X4	(M4X4& m4x4target_ref, const M4X4& m4x4_ref);
	bool	MulMtx4X4	(VEC& vtarget_ref, const M4X4& m4x4_ref, const VEC& v_ref);
};

#endif MATHMANIPULATIONS_H





