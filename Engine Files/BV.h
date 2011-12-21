////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	BV.h
////////////////////////////////////////////////

/*
NOTE:
	This is the bounding volume class.  It contains
	a bounding sphere, and will soon contain a
	bounding box, for complex collision detection.
*/

#ifndef BV_H
#define BV_H

#include "EngineMechanics.h"
#include "BS.h"

/////////////////////////////////////////////

struct BV {

public:

	//default constructor
	BV();
	//copy constructor
	BV(const BV& bv_ref);
	//complex construction
	BV(const BS& bs_ef);
	//destructor
	~BV();

	//bounding sphere
	BS bSphere;

};

#endif BV_H




