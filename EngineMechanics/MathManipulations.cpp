////////////////////////////////////////////////
//	Martin Goulet
//	Project:
//	MathManipulations.cpp
////////////////////////////////////////////////

#include "MathManipulations.h"

namespace MathManipulations
{

////////////////////////////////////////////////
//explicit vectorial opeartor overloaders
////////////////////////////////////////////////
	bool MathManipulations::AddVEC(VEC& vtarget_ref, const VEC& v_ref)
	{
		for (int i = 0; i < 3; i++)
		{
			vtarget_ref.fCoords[i]+= v_ref.fCoords[i];
		}
		return true;
	}
////////////////////////////////////////////////
	//method that adds to FIRST parameter the values of the SECOND parameter
	bool MathManipulations::AddVEC(VEC& vtarget_ref, const VEC& v1_ref, const VEC& v2_ref)
	{
		for (int i = 0; i < 3; i++)
		{
			vtarget_ref.fCoords[i] = v1_ref.fCoords[i] + v2_ref.fCoords[i];
		}
		return true;
	}
////////////////////////////////////////////////
	bool MathManipulations::SubVEC(VEC& vtarget_ref, const VEC& v_ref)
	{
		for (int i = 0; i < 3; i++)
		{
			vtarget_ref.fCoords[i]-= v_ref.fCoords[i];
		}
		return true;
	}
////////////////////////////////////////////////
	//method that adds to FIRST parameter the values of the SECOND parameter
	bool MathManipulations::SubVEC(VEC& vtarget_ref, const VEC& v1_ref, const VEC& v2_ref)
	{
		for (int i = 0; i < 3; i++)
		{
			vtarget_ref.fCoords[i] = v1_ref.fCoords[i] - v2_ref.fCoords[i];
		}
		return true;
	}
////////////////////////////////////////////////
	bool MathManipulations::MulVEC( VEC& v_ref, float f)
	{
		for (int i = 0; i < 3; i++) {
			v_ref.fCoords[i] *= f;
		}
		return true;
	}
////////////////////////////////////////////////
	//calculates the length of a VECTOR
	float MathManipulations::SizVEC(const VEC& v_ref)
	{
		return sqrt(pow(v_ref.fCoords[0],2) +
					 pow(v_ref.fCoords[1],2) +
					 pow(v_ref.fCoords[2],2) );
	}
////////////////////////////////////////////////
//trivial structure manipulations
////////////////////////////////////////////////
	//inverts a vector in parameter (pointer)
	bool MathManipulations::InvVEC(VEC& v_ref)
	{
		v_ref.fCoords[0] *= -1;
		v_ref.fCoords[1] *= -1;
		v_ref.fCoords[2] *= -1;
		return true;
	}
////////////////////////////////////////////////
	//normalizez the VECTOR given in parameter
	bool MathManipulations::NorVEC(VEC& v_ref)
	{
		float fSize = SizVEC(v_ref);
		//error check
		if (fSize <= 0)
		{
			v_ref.fCoords[0] == 0;
			v_ref.fCoords[1] == 0;
			v_ref.fCoords[2] == 0;
			return false;
		}
		v_ref.fCoords[0] /= fSize;
		v_ref.fCoords[1] /= fSize;
		v_ref.fCoords[2] /= fSize;
		return true;
	}
////////////////////////////////////////////////
	//computes cross product with 2 vectors
	bool MathManipulations::CroVEC(VEC& vtarget_ref, const VEC& v1_ref, const VEC& v2_ref)
	{
		vtarget_ref.fCoords[0] =	(v1_ref.fCoords[1] * v2_ref.fCoords[2]) -
									(v1_ref.fCoords[2] * v2_ref.fCoords[1]);
		vtarget_ref.fCoords[1] =	(v1_ref.fCoords[2] * v2_ref.fCoords[0]) -
									(v1_ref.fCoords[0] * v2_ref.fCoords[2]);
		vtarget_ref.fCoords[2] =	(v1_ref.fCoords[0] * v2_ref.fCoords[1]) -
									(v1_ref.fCoords[1] * v2_ref.fCoords[0]);
		return true;
	}
////////////////////////////////////////////////
	//computation of dot product (returns the dot product value)
	float MathManipulations::DotVEC(const VEC& v1_ref, const VEC& v2_ref)
	{
		return (	v1_ref.fCoords[0] * v2_ref.fCoords[0] +
					v1_ref.fCoords[1] * v2_ref.fCoords[1] +
					v1_ref.fCoords[2] * v2_ref.fCoords[2]	);
	}
////////////////////////////////////////////////
	//relative tristate method
	//returns a ternary state: -1, 0, 1 determining wether a value is smaller, bigger or equal
	//to a CentreBit with a specific error equality margin.
	float MathManipulations::RtsCHK(float fCentreBit, float fErrorBit, float fResultToClassify)
	{
		if (fResultToClassify < fCentreBit - fErrorBit) return -1;
		if (fResultToClassify > fCentreBit + fErrorBit) return 1;
		return 0;
	}
////////////////////////////////////////////////
	///method that finds the angle between two vectors, with proper arc function
	float MathManipulations::FndDeg(const VEC& v1_ref, const VEC& v2_ref)
	{
		//vectors to be used
		VEC v1 = v1_ref;
		VEC v2 = v2_ref;
		MathManipulations::NorVEC(v1);
		MathManipulations::NorVEC(v2);
		//dot product
		float fDot = MathManipulations::DotVEC(v1, v2);
		//cross product
		VEC vCro;
		MathManipulations::CroVEC(vCro, v1, v2);
		float fCro = MathManipulations::SizVEC(vCro);
		//calculating angle
		float fDegAngle = acos(fDot) * 180 / 3.1415927;
		//return angle
		return fDegAngle;
	}

////////////////////////////////////////////////
	//method that returns a bool verdict of parallelism of 2 vectors,
	//given an angle error margin
	bool MathManipulations::PrlCHK(const PLN& pln_ref, const TRI& tri_ref)
	{
		//temporary normal vector
		VEC vNormalToTri, vFinalResult;
		//vectors used to calculate cross pruduct of current polygon
		VEC v1, v2;
		SubVEC(v1, tri_ref.vVertices[1], tri_ref.vVertices[0]);
		SubVEC(v2, tri_ref.vVertices[2], tri_ref.vVertices[0]);
		//calculation of VECTOR normal to current POLYGON
		CroVEC(vNormalToTri, v1, v2);
		CroVEC(vFinalResult, vNormalToTri, pln_ref.vNormalVector);
		float fResult = SizVEC(vFinalResult);
		//returning result
		if (fResult < -0.0005) { return false; }
		if (fResult > 0.0005) { return false; }
		
		return true;	//fResult is > -0.0005 AND < 0.0005
	}
	

////////////////////////////////////////////////
//compound structure manipulations
////////////////////////////////////////////////
	
	//finsing the intersection VECTOR of a RAY and PLANE
	bool MathManipulations::IntLINPLN(VEC& v_ref, const LIN& lin_ref, const PLN& pln_ref)
	{
		//RAY:		(x,y,z) = k(dx,dy,dz) + (bx,by,bz)
		//PLANE:	Ax + By + Cz = D
		//Therefore: k = [ D - A(bx)+B(by)+C(bz) ] / [ A(dx)+B(dy)+C(dz) ]

		//fK = D
		float fK = pln_ref.fDotProduct;
		//fK = [ D - ( A(bx)+B(by)+C(bz) ) ]
		fK = fK-(pln_ref.vNormalVector.fCoords[0]*lin_ref.vBase.fCoords[0])-
				(pln_ref.vNormalVector.fCoords[1]*lin_ref.vBase.fCoords[1])-
				(pln_ref.vNormalVector.fCoords[2]*lin_ref.vBase.fCoords[2]);

		//fDenominator [ A(dx)+B(dy)+C(dz) ]
		float fDenominator =
		pln_ref.vNormalVector.fCoords[0]*lin_ref.vDirection.fCoords[0]+
		pln_ref.vNormalVector.fCoords[1]*lin_ref.vDirection.fCoords[1]+
		pln_ref.vNormalVector.fCoords[2]*lin_ref.vDirection.fCoords[2];
		//fK =  [ D - A(bx)+B(by)+C(bz) ] / [ A(dx)+B(dy)+C(dz) ]

		//error check
		if ( (float)RtsCHK(0,0.000005, fDenominator) == 0 ) { return false; }

		fK /= fDenominator;
		//change the values of ray_ptr in a parametric fashion
		v_ref.fCoords[0] = lin_ref.vDirection.fCoords[0]*fK + lin_ref.vBase.fCoords[0];
		v_ref.fCoords[1] = lin_ref.vDirection.fCoords[1]*fK + lin_ref.vBase.fCoords[1];
		v_ref.fCoords[2] = lin_ref.vDirection.fCoords[2]*fK + lin_ref.vBase.fCoords[2];
		return true;
	}

////////////////////////////////////////////////
	// [ m0 m3 m6 ]
	// [ m1 m4 m7 ]
	// [ m2 m5 m8 ]

	float MathManipulations::DetMtx3X3(const M3X3& m3x3_ref)
	{
		//positive diagonal branches
		float fAdd =
			m3x3_ref.fCoords[0]*m3x3_ref.fCoords[4]*m3x3_ref.fCoords[8]+
			m3x3_ref.fCoords[3]*m3x3_ref.fCoords[7]*m3x3_ref.fCoords[2]+
			m3x3_ref.fCoords[6]*m3x3_ref.fCoords[1]*m3x3_ref.fCoords[5];
		//negative diagonal branches
		float fSub =
			m3x3_ref.fCoords[2]*m3x3_ref.fCoords[4]*m3x3_ref.fCoords[6]+
			m3x3_ref.fCoords[5]*m3x3_ref.fCoords[7]*m3x3_ref.fCoords[0]+
			m3x3_ref.fCoords[8]*m3x3_ref.fCoords[1]*m3x3_ref.fCoords[3];

		return fAdd-fSub;
	}

////////////////////////////////////////////////

	bool MathManipulations::RotMtx3X3(VEC& vtarget_ref, const VEC& vaxis_ref, float fangle)
	{
		//check to see if rotation axis VEC is normalized; if not, error
		if ( (SizVEC(vaxis_ref) < 0.99) || (SizVEC(vaxis_ref) > 1.01) )
		{
			return false;
		}

		//COS and SIN calculations
		float fCos = cos(fangle);
		float fSin = sin(fangle);

		//calculation of the nine matrix positions
		//first row
		float fPos11 = fCos + (1-fCos)*pow(vaxis_ref.fCoords[0],2);
		float fPos12 = ((1-fCos)*vaxis_ref.fCoords[0]*vaxis_ref.fCoords[1]) - fSin*vaxis_ref.fCoords[2];
		float fPos13 = ((1-fCos)*vaxis_ref.fCoords[0]*vaxis_ref.fCoords[2]) + fSin*vaxis_ref.fCoords[1];
		//second row
		float fPos21 = ((1-fCos)*vaxis_ref.fCoords[0]*vaxis_ref.fCoords[1]) + fSin*vaxis_ref.fCoords[2];
		float fPos22 = fCos + (1-fCos)*pow(vaxis_ref.fCoords[1],2);
		float fPos23 = ((1-fCos)*vaxis_ref.fCoords[1]*vaxis_ref.fCoords[2]) - fSin*vaxis_ref.fCoords[0];
		//third row
		float fPos31 = ((1-fCos)*vaxis_ref.fCoords[0]*vaxis_ref.fCoords[2]) - fSin*vaxis_ref.fCoords[1];
		float fPos32 = ((1-fCos)*vaxis_ref.fCoords[1]*vaxis_ref.fCoords[2]) + fSin*vaxis_ref.fCoords[0];
		float fPos33 = fCos + (1-fCos)*pow(vaxis_ref.fCoords[2],2);

		//storing old VEC values for computation
		float fOldX = vtarget_ref.fCoords[0];
		float fOldY = vtarget_ref.fCoords[1];
		float fOldZ = vtarget_ref.fCoords[2];

		//assigning actual rotation to target VEC
		vtarget_ref.fCoords[0] = fPos11*fOldX + fPos12*fOldY + fPos13*fOldZ;
		vtarget_ref.fCoords[1] = fPos21*fOldX + fPos22*fOldY + fPos23*fOldZ;
		vtarget_ref.fCoords[2] = fPos31*fOldX + fPos32*fOldY + fPos33*fOldZ;

		//temp return true
		return true;
	}

////////////////////////////////////////////////

	bool MathManipulations::MulMtx3X3(M3X3& m3x3_ref, float f)
	{
		for (int i = 0; i < 9; i++)
		{
			m3x3_ref.fCoords[i] *= f;
		}
		return true;
	}
////////////////////////////////////////////////
	// [ m0 m3 m6 ]
	// [ m1 m4 m7 ]
	// [ m2 m5 m8 ]
	bool MathManipulations::MulMtx3X3(M3X3& m3x3target_ref, const M3X3& m3x3_ref)
	{
		M3X3 mTemp;
		mTemp.fCoords[0] =	m3x3target_ref.fCoords[0]*m3x3_ref.fCoords[0]+
							m3x3target_ref.fCoords[3]*m3x3_ref.fCoords[1]+
							m3x3target_ref.fCoords[6]*m3x3_ref.fCoords[2];
		mTemp.fCoords[1] =	m3x3target_ref.fCoords[1]*m3x3_ref.fCoords[0]+
							m3x3target_ref.fCoords[4]*m3x3_ref.fCoords[1]+
							m3x3target_ref.fCoords[7]*m3x3_ref.fCoords[2];
		mTemp.fCoords[2] =	m3x3target_ref.fCoords[2]*m3x3_ref.fCoords[0]+
							m3x3target_ref.fCoords[5]*m3x3_ref.fCoords[1]+
							m3x3target_ref.fCoords[8]*m3x3_ref.fCoords[2];

		mTemp.fCoords[3] =	m3x3target_ref.fCoords[0]*m3x3_ref.fCoords[3]+
							m3x3target_ref.fCoords[3]*m3x3_ref.fCoords[4]+
							m3x3target_ref.fCoords[6]*m3x3_ref.fCoords[5];
		mTemp.fCoords[4] =	m3x3target_ref.fCoords[1]*m3x3_ref.fCoords[3]+
							m3x3target_ref.fCoords[4]*m3x3_ref.fCoords[4]+
							m3x3target_ref.fCoords[7]*m3x3_ref.fCoords[5];
		mTemp.fCoords[5] =	m3x3target_ref.fCoords[2]*m3x3_ref.fCoords[3]+
							m3x3target_ref.fCoords[5]*m3x3_ref.fCoords[4]+
							m3x3target_ref.fCoords[8]*m3x3_ref.fCoords[5];

		mTemp.fCoords[6] =	m3x3target_ref.fCoords[0]*m3x3_ref.fCoords[6]+
							m3x3target_ref.fCoords[3]*m3x3_ref.fCoords[7]+
							m3x3target_ref.fCoords[6]*m3x3_ref.fCoords[8];
		mTemp.fCoords[7] =	m3x3target_ref.fCoords[1]*m3x3_ref.fCoords[6]+
							m3x3target_ref.fCoords[4]*m3x3_ref.fCoords[7]+
							m3x3target_ref.fCoords[7]*m3x3_ref.fCoords[8];
		mTemp.fCoords[8] =	m3x3target_ref.fCoords[2]*m3x3_ref.fCoords[6]+
							m3x3target_ref.fCoords[5]*m3x3_ref.fCoords[7]+
							m3x3target_ref.fCoords[8]*m3x3_ref.fCoords[8];

		m3x3target_ref = mTemp;
		return true;
	}

////////////////////////////////////////////////
	// [ m0 m3 m6 ]
	// [ m1 m4 m7 ]
	// [ m2 m5 m8 ]
	bool MathManipulations::TrsMtx3X3(M3X3& m3x3_ref)
	{
		//calculate 3x3 transpose
		M3X3 mTranspose;
		mTranspose.fCoords[0] = m3x3_ref.fCoords[0];
		mTranspose.fCoords[1] = m3x3_ref.fCoords[3];
		mTranspose.fCoords[2] = m3x3_ref.fCoords[6];
		mTranspose.fCoords[3] = m3x3_ref.fCoords[1];
		mTranspose.fCoords[4] = m3x3_ref.fCoords[4];
		mTranspose.fCoords[5] = m3x3_ref.fCoords[7];
		mTranspose.fCoords[6] = m3x3_ref.fCoords[2];
		mTranspose.fCoords[7] = m3x3_ref.fCoords[5];
		mTranspose.fCoords[8] = m3x3_ref.fCoords[8];

		//copy and return
		m3x3_ref = mTranspose;

		return true;
	}

////////////////////////////////////////////////
	// [ m0 m3 m6 ]
	// [ m1 m4 m7 ]
	// [ m2 m5 m8 ]

	bool MathManipulations::InvMtx3X3(M3X3& m3x3_ref)
	{
		float fDet = MathManipulations::DetMtx3X3(m3x3_ref);
		//check to see if determinant is zero
		
		if ( MathManipulations::RtsCHK(0, 0.000005, fDet) == 0 )
		{
			return false;
		}
		
		
		//inverse of the det value
		float fInvDet = 1.0f / fDet;

		//the adjoint matrix to construct
		M3X3 adjoint3x3;
		//calculate matrix minors
		adjoint3x3.fCoords[0] =	(m3x3_ref.fCoords[4]*m3x3_ref.fCoords[8])-
								(m3x3_ref.fCoords[5]*m3x3_ref.fCoords[7]);
		adjoint3x3.fCoords[1] =	(m3x3_ref.fCoords[3]*m3x3_ref.fCoords[8])-
								(m3x3_ref.fCoords[5]*m3x3_ref.fCoords[6]);
		adjoint3x3.fCoords[2] =	(m3x3_ref.fCoords[3]*m3x3_ref.fCoords[7])-
								(m3x3_ref.fCoords[4]*m3x3_ref.fCoords[6]);
		adjoint3x3.fCoords[3] =	(m3x3_ref.fCoords[1]*m3x3_ref.fCoords[8])-
								(m3x3_ref.fCoords[2]*m3x3_ref.fCoords[7]);
		adjoint3x3.fCoords[4] =	(m3x3_ref.fCoords[0]*m3x3_ref.fCoords[8])-
								(m3x3_ref.fCoords[2]*m3x3_ref.fCoords[6]);
		adjoint3x3.fCoords[5] =	(m3x3_ref.fCoords[0]*m3x3_ref.fCoords[7])-
								(m3x3_ref.fCoords[1]*m3x3_ref.fCoords[6]);
		adjoint3x3.fCoords[6] =	(m3x3_ref.fCoords[1]*m3x3_ref.fCoords[5])-
								(m3x3_ref.fCoords[2]*m3x3_ref.fCoords[4]);
		adjoint3x3.fCoords[7] =	(m3x3_ref.fCoords[0]*m3x3_ref.fCoords[5])-
								(m3x3_ref.fCoords[2]*m3x3_ref.fCoords[3]);
		adjoint3x3.fCoords[8] = (m3x3_ref.fCoords[0]*m3x3_ref.fCoords[4])-
								(m3x3_ref.fCoords[1]*m3x3_ref.fCoords[3]);

		//adjust matrix cofacs
		adjoint3x3.fCoords[1] *= -1;
		adjoint3x3.fCoords[3] *= -1;
		adjoint3x3.fCoords[5] *= -1;
		adjoint3x3.fCoords[7] *= -1;

		//transpose matrix
		MathManipulations::TrsMtx3X3(adjoint3x3);

		//multiply by 1/determinant
		MathManipulations::MulMtx3X3(adjoint3x3, fInvDet);

		//copy the matrix in the parameter
		m3x3_ref = adjoint3x3;

		return true;
	}

////////////////////////////////////////////////
//4x4 matrix manipulations
////////////////////////////////////////////////
	// [ m0 m3 m6 ]    [ m0 m3 m6 0 ]
	// [ m1 m4 m7 ] -> [ m1 m4 m7 0 ]
	// [ m2 m5 m8 ]    [ m2 m5 m8 0 ]
	//				   [ 0  0  0  1 ]

	bool MathManipulations::CpyMtx4X4(M4X4& m4x4_ref, const M3X3& m3x3_ref)
	{
		//first column
		m4x4_ref.fCoords[0] = m3x3_ref.fCoords[0];
		m4x4_ref.fCoords[1] = m3x3_ref.fCoords[1];
		m4x4_ref.fCoords[2] = m3x3_ref.fCoords[2];
		m4x4_ref.fCoords[3] = 0;
		//second column
		m4x4_ref.fCoords[4] = m3x3_ref.fCoords[3];
		m4x4_ref.fCoords[5] = m3x3_ref.fCoords[4];
		m4x4_ref.fCoords[6] = m3x3_ref.fCoords[5];
		m4x4_ref.fCoords[7] = 0;
		//3rd column
		m4x4_ref.fCoords[8] = m3x3_ref.fCoords[6];
		m4x4_ref.fCoords[9] = m3x3_ref.fCoords[7];
		m4x4_ref.fCoords[10] = m3x3_ref.fCoords[8];
		m4x4_ref.fCoords[11] = 0;
		//4th column
		m4x4_ref.fCoords[12] = 0;
		m4x4_ref.fCoords[13] = 0;
		m4x4_ref.fCoords[14] = 0;
		m4x4_ref.fCoords[15] = 1;

		return true;
	}

////////////////////////////////////////////////
	bool MathManipulations::MulMtx4X4(M4X4& m4x4_ref, float f)
	{
		for (int i = 0; i < 16; i++)
		{
			m4x4_ref.fCoords[i] *= f;
		}
		return true;
	}
////////////////////////////////////////////////
	// [ m0  m4  m8  m12 ]
	// [ m1  m5  m9  m13 ]
	// [ m2  m6  m10 m14 ]
	// [ m3  m7  m11 m15 ]
	bool MathManipulations::MulMtx4X4(M4X4& m4x4target_ref, const M4X4& m4x4_ref)
	{
		M4X4 mTemp;

		//first column
		mTemp.fCoords[0] =	m4x4target_ref.fCoords[0]*m4x4_ref.fCoords[0]+
							m4x4target_ref.fCoords[4]*m4x4_ref.fCoords[1]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[2]+
							m4x4target_ref.fCoords[12]*m4x4_ref.fCoords[3];
		mTemp.fCoords[1] =	m4x4target_ref.fCoords[1]*m4x4_ref.fCoords[0]+
							m4x4target_ref.fCoords[5]*m4x4_ref.fCoords[1]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[2]+
							m4x4target_ref.fCoords[13]*m4x4_ref.fCoords[3];
		mTemp.fCoords[2] =	m4x4target_ref.fCoords[2]*m4x4_ref.fCoords[0]+
							m4x4target_ref.fCoords[6]*m4x4_ref.fCoords[1]+
							m4x4target_ref.fCoords[10]*m4x4_ref.fCoords[2]+
							m4x4target_ref.fCoords[14]*m4x4_ref.fCoords[3];
		mTemp.fCoords[3] =	m4x4target_ref.fCoords[3]*m4x4_ref.fCoords[0]+
							m4x4target_ref.fCoords[7]*m4x4_ref.fCoords[1]+
							m4x4target_ref.fCoords[11]*m4x4_ref.fCoords[2]+
							m4x4target_ref.fCoords[15]*m4x4_ref.fCoords[3];
		//second column
		mTemp.fCoords[4] =	m4x4target_ref.fCoords[0]*m4x4_ref.fCoords[4]+
							m4x4target_ref.fCoords[4]*m4x4_ref.fCoords[5]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[6]+
							m4x4target_ref.fCoords[12]*m4x4_ref.fCoords[7];
		mTemp.fCoords[5] =	m4x4target_ref.fCoords[1]*m4x4_ref.fCoords[4]+
							m4x4target_ref.fCoords[5]*m4x4_ref.fCoords[5]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[6]+
							m4x4target_ref.fCoords[13]*m4x4_ref.fCoords[7];
		mTemp.fCoords[6] =	m4x4target_ref.fCoords[2]*m4x4_ref.fCoords[4]+
							m4x4target_ref.fCoords[6]*m4x4_ref.fCoords[5]+
							m4x4target_ref.fCoords[10]*m4x4_ref.fCoords[6]+
							m4x4target_ref.fCoords[14]*m4x4_ref.fCoords[7];
		mTemp.fCoords[7] =	m4x4target_ref.fCoords[3]*m4x4_ref.fCoords[4]+
							m4x4target_ref.fCoords[7]*m4x4_ref.fCoords[5]+
							m4x4target_ref.fCoords[11]*m4x4_ref.fCoords[6]+
							m4x4target_ref.fCoords[15]*m4x4_ref.fCoords[7];
		//third column
		mTemp.fCoords[8] =	m4x4target_ref.fCoords[0]*m4x4_ref.fCoords[8]+
							m4x4target_ref.fCoords[4]*m4x4_ref.fCoords[9]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[10]+
							m4x4target_ref.fCoords[12]*m4x4_ref.fCoords[11];
		mTemp.fCoords[9] =	m4x4target_ref.fCoords[1]*m4x4_ref.fCoords[8]+
							m4x4target_ref.fCoords[5]*m4x4_ref.fCoords[9]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[10]+
							m4x4target_ref.fCoords[13]*m4x4_ref.fCoords[11];
		mTemp.fCoords[10] =	m4x4target_ref.fCoords[2]*m4x4_ref.fCoords[8]+
							m4x4target_ref.fCoords[6]*m4x4_ref.fCoords[9]+
							m4x4target_ref.fCoords[10]*m4x4_ref.fCoords[10]+
							m4x4target_ref.fCoords[14]*m4x4_ref.fCoords[11];
		mTemp.fCoords[11] =	m4x4target_ref.fCoords[3]*m4x4_ref.fCoords[8]+
							m4x4target_ref.fCoords[7]*m4x4_ref.fCoords[9]+
							m4x4target_ref.fCoords[11]*m4x4_ref.fCoords[10]+
							m4x4target_ref.fCoords[15]*m4x4_ref.fCoords[11];
		//fourth column
		mTemp.fCoords[12] =	m4x4target_ref.fCoords[0]*m4x4_ref.fCoords[12]+
							m4x4target_ref.fCoords[4]*m4x4_ref.fCoords[13]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[14]+
							m4x4target_ref.fCoords[12]*m4x4_ref.fCoords[15];
		mTemp.fCoords[13] =	m4x4target_ref.fCoords[1]*m4x4_ref.fCoords[12]+
							m4x4target_ref.fCoords[5]*m4x4_ref.fCoords[13]+
							m4x4target_ref.fCoords[8]*m4x4_ref.fCoords[14]+
							m4x4target_ref.fCoords[13]*m4x4_ref.fCoords[15];
		mTemp.fCoords[14] =	m4x4target_ref.fCoords[2]*m4x4_ref.fCoords[12]+
							m4x4target_ref.fCoords[6]*m4x4_ref.fCoords[13]+
							m4x4target_ref.fCoords[10]*m4x4_ref.fCoords[14]+
							m4x4target_ref.fCoords[14]*m4x4_ref.fCoords[15];
		mTemp.fCoords[15] =	m4x4target_ref.fCoords[3]*m4x4_ref.fCoords[12]+
							m4x4target_ref.fCoords[7]*m4x4_ref.fCoords[13]+
							m4x4target_ref.fCoords[11]*m4x4_ref.fCoords[14]+
							m4x4target_ref.fCoords[15]*m4x4_ref.fCoords[15];
		m4x4target_ref = mTemp;

		return true;
	}

////////////////////////////////////////////////
	// [ m0  m4  m8  m12 ]
	// [ m1  m5  m9  m13 ]
	// [ m2  m6  m10 m14 ]
	// [ m3  m7  m11 m15 ]
	bool MathManipulations::MulMtx4X4(VEC& vtarget_ref, const M4X4& m4x4_ref, const VEC& v_ref)
	{
		//temp vetor
		VEC vResult;
		//multiply
		for (int i = 0; i < 4; i++)
		{
			vResult.fCoords[i] =	v_ref.fCoords[0] * m4x4_ref.fCoords[i]+
									v_ref.fCoords[1] * m4x4_ref.fCoords[i+4]+
									v_ref.fCoords[2] * m4x4_ref.fCoords[i+8]+
									v_ref.fCoords[3] * m4x4_ref.fCoords[i+12];
		}
		//copy
		vtarget_ref = vResult;

		return true;
	}

////////////////////////////////////////////////
};




