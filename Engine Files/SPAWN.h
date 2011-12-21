////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	SPAWN.h
////////////////////////////////////////////////

/*
NOTE:

*/

#ifndef SPAWN_H
#define SPAWN_H

#include "EE.h"

class SPAWN: public EE
{
private:
	//***VARIABLES***

public:
	//CONSTRUCTORS/DESTRUCTOR***
	SPAWN();
	SPAWN(const VEC& v1_ref, const VEC& v2_ref, const VEC& v3_ref, float fH);
	SPAWN(const SPAWN& s_ref);
	~SPAWN();
    
	//***METHODS***
	bool Init();
	bool Release();
};

#endif SPAWN_H