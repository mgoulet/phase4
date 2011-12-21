////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase4
//	DE.h
////////////////////////////////////////////////

/*
NOTE:
	This class is the standard dynamical abstract
	class.  All dynamical entities will inherit
	this class.
*/

#ifndef DE_H
#define DE_H

//includes
#include <string>
#include "EngineMechanics.h"
#include "GE.h"
#include "GeneralDynamicsData.h"
using namespace std;

class DE: public GE
{
public:

	//copy constructor
	DE(const DE& de_ref);
	//complex construction
	DE(	/*GE parameters*/int iType, string sName,
		/*member parameters*/float fMass, float fForce, float fHyper,
							 const VEC* vSVS_ptr, const float* fHVS_ptr);

	//destructor
	virtual ~DE();

	//entity mass
	float fMass;
	//entity accel force
	float fForce;
	//entity hyper force
	float fHyper;

	/*
	standard vector set, describing a dynamic entity's
	position, orientation and dynamics vectors in 3d space.
	vStandardVectorSet[0] = Position VEC
	vStandardVectorSet[1] = Direction VEC
	vStandardVectorSet[2] = Normal (UP) VEC
	vStandardVectorSet[3] = Velocity VEC
	vStandardVectorSet[4] = Acceleration VEC
	*/
	VEC vSVS[5];

	/*
	hyper value set, describing a dynamic entity's
	position and dynamics through the hyperfactor.
	fHyperValueSet[0] = hyperposition
	fHyperValueSet[1] = hypervelocity
	fHyperValueSet[2] = hyperacceleration
	*/
	float fHVS[3];

	//pitch rotation
	void Pitch (float fAngle);
	//yaw rotation
	void Yaw (float fAngle);
	//roll rotation
	void Roll (float fAngle);

	void CopySVS(const VEC* vSVS_ptr);
	void CopyHVS(const float* fHVS_ptr);

	//update accel & velocities according to input
	virtual void CalcInputDynamics(const bool* bThrottleSet_ptr) = 0;
	//update accel & velocity automatically (no input control)
	virtual void CalcAutoDynamics() = 0;
	//***APPLY DYNAMICS***
	virtual void ApplyDynamics(float fDt) = 0;

};


#endif DE_H

