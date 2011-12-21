/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//EntityManager.h
/////////////////////////////////////////////////////////////////

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

//includes
#include <iostream>
#include <iterator>
#include "SubComponent.h"
#include "Timer.h"
#include "Console.h"
#include "InputManager.h"
#include "EntitySet.h"
#include "HeightMap.h"
#include "EngineMechanics.h"
#include "EngineEntities.h"
using namespace std;


class EntityManager: public SubComponent
{
public:

	//constructors/destructor
	EntityManager();
	~EntityManager();

	//environmental slice
	bool RunEnvironmentalSlice(	Timer& timer_ref,
								Console& console_ref,
								InputManager& inputmanager_ref,
								EntitySet& entityset_ref,
								HeightMap& heightmap_ref) const;
    
private:

	//init/release methods
	bool Init();
	bool Release();

	//ICC increment methods
	bool UpdateCameraCycle(	Timer& timer_ref,
							Console& console_ref,
							InputManager& inputmanager_ref,
							EntitySet& entityset_ref) const;

	bool UpdateControlCycle(	Timer& timer_ref,
								Console& console_ref,
								InputManager& inputmanager_ref,
								EntitySet& entityset_ref) const;

	bool UpdateEntityControl(	Timer& timer_ref,
								Console& console_ref,
								InputManager& inputmanager_ref,
								EntitySet& entityset_ref) const;

	bool UpdateCollisionCheck(	Timer& timer_ref,
								Console& console_ref,
								InputManager& inputmanager_ref,
								EntitySet& entityset_ref) const;


	bool UpdateEntityDynamics(	Timer& timer_ref,
								Console& console_ref,
								InputManager& inputmanager_ref,
								EntitySet& entityset_ref,
								HeightMap& heightmap_ref) const;
};


#endif ENTITYMANAGER_H