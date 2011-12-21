/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//EntityManager.cpp
/////////////////////////////////////////////////////////////////

#include "EntityManager.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTOR/DESTRUCTOR
/////////////////////////////////////////////////////////////////

EntityManager::EntityManager()
{
	this->Init();
}

EntityManager::~EntityManager()
{
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool EntityManager::Init()
{
	return true;
}

bool EntityManager::Release()
{
	return true;
}

bool EntityManager::RunEnvironmentalSlice(	Timer& timer_ref,
											Console& console_ref,
											InputManager& inputmanager_ref,
											EntitySet& entityset_ref,
											HeightMap& heightmap_ref) const
{

	//update camera target
	this->UpdateCameraCycle(	timer_ref,
								console_ref,
								inputmanager_ref,
								entityset_ref);
	//update control target
	this->UpdateControlCycle(	timer_ref,
								console_ref,
								inputmanager_ref,
								entityset_ref);

	//update control target acceleration and other variables
	this->UpdateEntityControl(	timer_ref,
								console_ref,
								inputmanager_ref,
								entityset_ref);

	//check for collisions and apply them
	this->UpdateCollisionCheck(	timer_ref,
								console_ref,
								inputmanager_ref,
								entityset_ref);

	//update entire entitylist, actual physical movements
	this->UpdateEntityDynamics(	timer_ref,
								console_ref,
								inputmanager_ref,
								entityset_ref,
								heightmap_ref);

	return true;
}

bool EntityManager::UpdateCameraCycle(	Timer& timer_ref,
										Console& console_ref,
										InputManager& inputmanager_ref,
										EntitySet& entityset_ref) const
{
	//console output management
	stringstream ss;
	string s;
	if (inputmanager_ref.GetNetInput().CycleCameraUp())
	{
		entityset_ref.CycleCameraTargetUp();
		ss << entityset_ref.GetCameraTargetID();
		ss >> s;
		console_ref.AppendToConsole("Cycling camera target to entity #" + s);
	}
	if (inputmanager_ref.GetNetInput().CycleCameraDown())
	{
		entityset_ref.CycleCameraTargetDown();
		ss << entityset_ref.GetCameraTargetID();
		ss >> s;
		console_ref.AppendToConsole("Cycling camera target to entity #" + s);
	}
	return true;
}

bool EntityManager::UpdateControlCycle(	Timer& timer_ref,
										Console& console_ref,
										InputManager& inputmanager_ref,
										EntitySet& entityset_ref) const
{
	//console output management
	stringstream ss;
	string s;

	if (inputmanager_ref.GetNetInput().CycleTargetUp())
	{
		entityset_ref.CycleControlTargetUp();
		ss << entityset_ref.GetControlTargetID();
		ss >> s;
		console_ref.AppendToConsole("Cycling control target to entity #" + s);
	}
	if (inputmanager_ref.GetNetInput().CycleTargetDown())
	{
		entityset_ref.CycleControlTargetDown();
		ss << entityset_ref.GetControlTargetID();
		ss >> s;
		console_ref.AppendToConsole("Cycling control target to entity #" + s);
	}

	return true;
}

bool EntityManager::UpdateEntityControl(Timer& timer_ref,
										Console& console_ref,
										InputManager& inputmanager_ref,
										EntitySet& entityset_ref) const
{
	//get pointer to control entity
	EE* ee_ptr = entityset_ref.list.at(entityset_ref.iControlTargetValue);

	//create throttle set to give to controlled entity
	bool bThrottleSet[8] = {inputmanager_ref.GetNetInput().Throttle(),
							inputmanager_ref.GetNetInput().ReverseThrottle(),
							inputmanager_ref.GetNetInput().StrafeUp(),
							inputmanager_ref.GetNetInput().StrafeDown(),
							inputmanager_ref.GetNetInput().StrafeLeft(),
							inputmanager_ref.GetNetInput().StrafeRight(),
							inputmanager_ref.GetNetInput().HyperUp(),
							inputmanager_ref.GetNetInput().HyperDown()};

	for (int i = 0; i < entityset_ref.GetNumberOfEntities(); i++)
	{
		//update orientation system, if entity is the control target
		if (i == entityset_ref.iControlTargetValue)
		{
			//update throttle system, according to control target
			entityset_ref.list.at(i)->CalcInputDynamics(bThrottleSet);
			//polling mouse movements
			entityset_ref.list.at(i)->Pitch((float)inputmanager_ref.GetNetInput().GetMouseY()/1000);
			entityset_ref.list.at(i)->Yaw(-(float)inputmanager_ref.GetNetInput().GetMouseX()/1000);
			//entity fire and stuff
			if (inputmanager_ref.GetNetInput().FirePrimary())
			{
				//copy svs & hvs
				VEC vSVS[5];
				for (int i = 0; i < 5; i++)
					vSVS[i] = ee_ptr->vSVS[i];
				float fHVS[3];
				for (int i = 0; i < 3; i++)
					fHVS[i] = ee_ptr->fHVS[i];
				//modify svs so that fire under chopter
				VEC vsub = ee_ptr->vSVS[2];
				MathManipulations::MulVEC(vsub, 0.5);
				MathManipulations::SubVEC(vSVS[0], vsub);

				//add rocket
				entityset_ref.AddToList(new ROCKET(vSVS, fHVS));
			}
		}
		else
		{
			entityset_ref.list.at(i)->CalcAutoDynamics();
		}
	}

	//glue camera to controlled entity
	entityset_ref.cam.GlueAllTo(*entityset_ref.GetCameraTargetRef());

	return true;
}

bool EntityManager::UpdateCollisionCheck(Timer& timer_ref,
										 Console& console_ref,
										 InputManager& inputmanager_ref,
										 EntitySet& entityset_ref) const
{
	//if there is only a single entity in the list, no collisions are made
	if (entityset_ref.GetNumberOfEntities() <= 1) return false;

	//reset collision bools
	for (int i = 0; i < entityset_ref.GetNumberOfEntities(); i++)
	{
		entityset_ref.list.at(i)->bIsColliding = false;
	}

	//otherwise, compare each pair for collision.
	for (int i = 0; i < entityset_ref.GetNumberOfEntities()-1; i++)
	{
		for (int j = i+1; j < entityset_ref.GetNumberOfEntities(); j++)
		{
			if (entityset_ref.list.at(i)->SphericalCollisionTest(*entityset_ref.list.at(j)))
			{
				//at this point, there was 3d collision

				//check if both entities are in hyperscope
				float fRelativeH = entityset_ref.list.at(j)->fHVS[0]-
					entityset_ref.GetList().at(i)->fHVS[0];
				//adjusting 
				if (fRelativeH >= 340) {fRelativeH -= 360;}
				if (fRelativeH <= -340) {fRelativeH += 360;}

				//adjust it as a percentage of 20 degrees
				fRelativeH = abs(fRelativeH);
				if (fRelativeH <= 20)
				{
					entityset_ref.list.at(i)->bIsColliding = true;
					entityset_ref.list.at(j)->bIsColliding = true;
				}
			}
		}
	}

	return true;
}

bool EntityManager::UpdateEntityDynamics(Timer& timer_ref,
										 Console& console_ref,
										 InputManager& inputmanager_ref,
										 EntitySet& entityset_ref,
										 HeightMap& heightmap_ref) const
{
/*
	stringstream ss;
	string s;
	ss << timer_ref.PollTimeInterval();
	ss >> s;
	console_ref.AppendToConsole("INTERVAL: " + s);
	//get pointer to control entity
	EE* ee_ptr = entityset_ref.list.at(entityset_ref.iControlTargetValue);
*/	

	for (int i = 0; i < entityset_ref.GetNumberOfEntities(); i++)
	{
		//process physics
		entityset_ref.list.at(i)->ApplyDynamics(timer_ref.PollTimeInterval());
	}

	return true;
}

