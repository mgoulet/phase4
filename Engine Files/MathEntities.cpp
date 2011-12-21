////////////////////////////////////////////////
//	Martin Goulet
//	Project:
//	MathEntities.h
////////////////////////////////////////////////

//this is the header file that contains the set of math
//entities such as the Vector, Ray, Plane and BSP.

#include "MathEntities.h"
////////////////////////////////////////////////
VEC::VEC()
		{
			for (int i = 0; i < 4; i++)
			{
				this->fCoords[i] = 0;
			}
		}

	//main-constructor
VEC::VEC(float f0, float f1, float f2, float f3)
	{
		this->fCoords[0] = f0;
		this->fCoords[1] = f1;
		this->fCoords[2] = f2;
		this->fCoords[3] = f3;
	}

	//copy-constructor
VEC::VEC(const VEC& vec_ref)
	{
		for (int i = 0; i < 4; i++)
		{
			this->fCoords[i] = vec_ref.fCoords[i];
		}
	}

	//detructor
VEC::~VEC() {}

////////////////////////////////////////////////

LIN::LIN() {}

	//main-constructor
LIN::LIN(const VEC& v1_ref, const VEC& v2_ref)
	{
		this->vBase = v1_ref;
		this->vDirection = v2_ref;
	}

	//copy-constructor
LIN::LIN(const LIN& lin_ref)
	{
		this->vBase = lin_ref.vBase;
		this->vDirection = lin_ref.vDirection;
	}

	//destructor
LIN::~LIN() {}
////////////////////////////////////////////////

//default-constructor
PLN::PLN() {}

	//main-constructor
PLN::PLN(const VEC& v1_ref, float f)
	{
		this->vNormalVector = v1_ref;
		this->fDotProduct = f;
	}

	//copy-constructor
PLN::PLN(const PLN& pln_ref)
	{
		this->fDotProduct = pln_ref.fDotProduct;
		this->vNormalVector = pln_ref.vNormalVector;
	}

PLN::~PLN()
	{

	}

////////////////////////////////////////////////

	//default-constructor
TRI::TRI() {}

	//main-constructor
TRI::TRI(const VEC& v0_ref, const VEC& v1_ref, const VEC& v2_ref)
	{
		this->vVertices[0] = v0_ref;
		this->vVertices[1] = v1_ref;
		this->vVertices[2] = v2_ref;
	}

	//copy-constructor
TRI::TRI(const TRI& tri_ref)
	{
		for (int i = 0; i < 3; i++)
		{
			this->vVertices[i] = tri_ref.vVertices[i];
		}
	}

	//destructor
TRI::~TRI() {}

////////////////////////////////////////////////

// [ m0 m3 m6 ]
// [ m1 m4 m7 ]
// [ m2 m5 m8 ]

	//default-constructor
M3X3::M3X3()
	{
		for (int i = 0; i < 9; i++)
		{
			this->fCoords[i] = 0;
		}
	}

	//main-constructor
M3X3::M3X3(float f0, float f1, float f2,
			float f3, float f4, float f5,
			float f6, float f7, float f8)
	{
		this->fCoords[0] = f0;
		this->fCoords[1] = f1;
		this->fCoords[2] = f2;
		this->fCoords[3] = f3;
		this->fCoords[4] = f4;
		this->fCoords[5] = f5;
		this->fCoords[6] = f6;
		this->fCoords[7] = f7;
		this->fCoords[8] = f8;
	}

	//copy-constructor
M3X3::M3X3(const M3X3& m3x3_ref)
	{
		for (int i = 0; i < 9; i++)
		{
			this->fCoords[i] = m3x3_ref.fCoords[i];
		}
	}

	//destructor
M3X3::~M3X3() {}

////////////////////////////////////////////////

// [ m0  m4  m8  m12 ]
// [ m1  m5  m9  m13 ]
// [ m2  m6  m10 m14 ]
// [ m3  m7  m11 m15 ]

//default-constructor
M4X4::M4X4() {}

	//main-constructor
M4X4::M4X4(float f0, float f1, float f2, float f3,
			float f4, float f5, float f6, float f7,
			float f8, float f9, float f10, float f11,
			float f12, float f13, float f14, float f15)
	{
		this->fCoords[0] = f0;
		this->fCoords[1] = f1;
		this->fCoords[2] = f2;
		this->fCoords[3] = f3;
		this->fCoords[4] = f4;
		this->fCoords[5] = f5;
		this->fCoords[6] = f6;
		this->fCoords[7] = f7;
		this->fCoords[8] = f8;
		this->fCoords[9] = f9;
		this->fCoords[10] = f10;
		this->fCoords[11] = f11;
		this->fCoords[12] = f12;
		this->fCoords[13] = f13;
		this->fCoords[14] = f14;
		this->fCoords[15] = f15;
	}

	//copy-constructor
M4X4::M4X4(const M4X4& m4x4_ref)
	{
		for (int i = 0; i < 16; i++)
		{
			this->fCoords[i] = m4x4_ref.fCoords[i];
		}
	}

	//destructor
M4X4::~M4X4() {}
