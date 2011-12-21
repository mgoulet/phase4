/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//EntitySet.h
/////////////////////////////////////////////////////////////////

#ifndef ENTITYSET_H
#define ENTITYSET_H

#include <deque>
#include "SubComponent.h"
#include "EngineMechanics.h"
#include "EngineEntities.h"

class EntitySet: public SubComponent
{
	friend class EntityManager;

public:
	//constructors/destructor
	EntitySet();
	~EntitySet();

	//accessors
	const CAM& GetCAM() const;
	const deque<EE*>& GetList() const;
	const EE* GetCameraTargetRef() const;
	const EE* GetControlTargetRef() const;

	int GetNumberOfEntities() const;
    int GetCameraTargetID() const;
	int GetControlTargetID() const;

	//cycling of control pointer
	bool CycleCameraTargetUp();
	bool CycleCameraTargetDown();
	bool CycleControlTargetUp();
	bool CycleControlTargetDown();

	//modifiers
	bool AddToList(EE* ee_ptr);
	bool RemoveFromList(int i);

private:
	//overriding methods
	bool Init();
	bool Release();

	//main game camera
	CAM cam;

	//camera target value
	int iCameraTargetValue;

	//object control pointer
	int iControlTargetValue;

	//main entity list
	deque<EE*> list;

};


#endif ENTITYSET_H