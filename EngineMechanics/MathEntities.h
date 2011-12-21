////////////////////////////////////////////////
//	Martin Goulet
//	Project:
//	MathEntities.h
////////////////////////////////////////////////

/*
NOTE:

*/

#ifndef MATHENTITIES_H
#define MATHENTITIES_H

//includes
#include <iostream>
#include <deque>
using namespace std;

////////////////////////////////////////////////
	struct VEC
	{

		//default-constructor
		VEC();

		//main-constructor
		VEC(float f0, float f1, float f2, float f3);

		//copy-constructor
		VEC(const VEC& vec_ref);

		//detructor
		~VEC();

		//float values
		float fCoords[4];

	};
////////////////////////////////////////////////
	struct LIN
	{

		//default-constructor
		LIN();

		//main-constructor
		LIN(const VEC& v1_ref, const VEC& v2_ref);

		//copy-constructor
		LIN(const LIN& lin_ref);

		//destructor
		~LIN();

		//vectors used to create line in 3d space
		VEC vBase;
		VEC vDirection;

	};
////////////////////////////////////////////////
	struct PLN
	{

		//default-constructor
		PLN();

		//main-constructor
		PLN(const VEC& v1_ref, float f);

		//copy-constructor
		PLN(const PLN& pln_ref);

		~PLN();

		//dot product value, representing distance from origin.
		float fDotProduct;

		//normal vector
		VEC vNormalVector;

	};
////////////////////////////////////////////////
	struct TRI
	{

		//default-constructor
		TRI();

		//main-constructor
		TRI(const VEC& v0_ref, const VEC& v1_ref, const VEC& v2_ref);

		//copy-constructor
		TRI(const TRI& tri_ref);

		//destructor
		~TRI();

		//vectors representing the summits of the TRI.
		VEC vVertices[3];

	};
////////////////////////////////////////////////

	// [ m0 m3 m6 ]
	// [ m1 m4 m7 ]
	// [ m2 m5 m8 ]

	struct M3X3
	{

		//default-constructor
		M3X3();

		//main-constructor
		M3X3(float f0, float f1, float f2,
			 float f3, float f4, float f5,
			 float f6, float f7, float f8);

		//copy-constructor
		M3X3(const M3X3& m3x3_ref);

		//destructor
		~M3X3();

		float fCoords[9];
	};

////////////////////////////////////////////////

	// [ m0  m4  m8  m12 ]
	// [ m1  m5  m9  m13 ]
	// [ m2  m6  m10 m14 ]
	// [ m3  m7  m11 m15 ]

	struct M4X4
	{
		//default-constructor
		M4X4();

		//main-constructor
		M4X4(float f0, float f1, float f2, float f3,
			 float f4, float f5, float f6, float f7,
			 float f8, float f9, float f10, float f11,
			 float f12, float f13, float f14, float f15);

		//copy-constructor
		M4X4(const M4X4& m4x4_ref);

		//destructor
		~M4X4();

		//coordinantes
		float fCoords[16];
	};

////////////////////////////////////////////////

#endif MATHENTITIES_H