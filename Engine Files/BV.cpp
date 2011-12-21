////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	BV.cpp
////////////////////////////////////////////////

#include "BV.h"

//default constructor
BV::BV()
:bSphere(BS())
{}

//copy constructor
BV::BV(const BV& bv_ref)
:bSphere(bv_ref.bSphere)
{}

//complex construction
BV::BV(const BS& bs_ref)
:bSphere(bs_ref)
{}

//destructor
BV::~BV()
{}	
