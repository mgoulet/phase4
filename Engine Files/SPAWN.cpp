////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	SPAWN.cpp
////////////////////////////////////////////////

/*
NOTE:

*/

#include "SPAWN.h"

////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
////////////////////////////////////////////////

SPAWN::SPAWN()
:EE(VEC(0,0,0,1), VEC(0,1,0,1), VEC(0,0,-1,1), 0, 2, -1, -1)
{
}

SPAWN::SPAWN(const VEC& v1_ref, const VEC& v2_ref, const VEC& v3_ref, float fH)
:EE(v1_ref, v2_ref, v3_ref, fH, 2, -1 ,-1)
{
}

SPAWN::SPAWN(const SPAWN& s_ref)
:EE(s_ref)
{
	//empty
}

SPAWN::~SPAWN()
{

}

////////////////////////////////////////////////
//METHODS
////////////////////////////////////////////////

bool SPAWN::Init()
{

	return true;
}

bool SPAWN::Release()
{

	return true;
}