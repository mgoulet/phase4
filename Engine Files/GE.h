////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	GE.h (GenericEntity)
////////////////////////////////////////////////

/*
NOTE:
This class represents the generic Environmental Entity
class, which will be abstract.  All the environmental entities
will inheit from this class.

	iType list:
	0		:	Camera (CAM)
	10 - 19	:	Ships (SHIP)
	20 - 29	:	Projectiles (PROJ)

*/

#ifndef GE_H
#define GE_H

#include <string>
using namespace std;
//class declaration
class GE
{

public:

	//default constructor
	GE();

	//copy constructor
	GE(const GE& ge_ref);

	//complex construction
	GE(/*member parameters*/int iType, string sName);

	//destructor
	virtual ~GE();

	//entity type
	int iType;

	//given name of entity
	string sName;

};

#endif GE_H

