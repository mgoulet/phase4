////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	GE.cpp
////////////////////////////////////////////////

#include "GE.h"

//default constructor
GE::GE()
{
	//default values
	this->iType = -1;
	this->sName = "Default Entity";
}

//copy construction
GE::GE(const GE& ge_ref)
{
	//entity type
	this->iType = ge_ref.iType;
	//copy name
	this->sName = ge_ref.sName;
}

//complex construction
GE::GE(/*member parameters*/int iType, string sName)
{
	//entity type
	this->iType = iType;
	//assign name
	this->sName = sName;
}

//destructor
GE::~GE()
{

}

