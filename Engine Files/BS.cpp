////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	SPHERE.cpp
////////////////////////////////////////////////

#include "BS.h"

////////////////////////////////////////////////
//CONSTRUCTORS//DESTRUCTOR
////////////////////////////////////////////////

//empty Construction
BS::BS()
{
	//set default radius value
	this->fRadius = 0.0f;
}

//copy constructor
BS::BS(const BS& bs_ref)
{
	//copy sphere radius
	this->fRadius = bs_ref.fRadius;
}

//coplex construction
BS::BS(float fRadius)
{
	//copy sphere radius
	this->fRadius = fRadius;
}

//destructor
BS::~BS()
{
	//empty
}




