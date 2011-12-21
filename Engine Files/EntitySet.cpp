/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//EntitySet.cpp
/////////////////////////////////////////////////////////////////

#include "EntitySet.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

EntitySet::EntitySet()
{
	this->Init();
}

EntitySet::~EntitySet()
{
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

//init/release methods
bool EntitySet::Init()
{
	//FIRST SQUADRON
	//create first SVS & HVS
	VEC v1SVS[5] = {VEC(-50,-150,0,1),   VEC(0,0,-1,0),VEC(0,1,0,0), VEC(0,0,0,0), VEC(0,0,0,0)};
	VEC v2SVS[5] = {VEC(-25,-150,0,1),   VEC(0,0,-1,0),VEC(0,1,0,0), VEC(0,0,0,0), VEC(0,0,0,0)};
	VEC v3SVS[5] = {VEC(  0,-150,0,1), VEC(0,0,-1,0),VEC(0,1,0,0), VEC(0,0,0,0), VEC(0,0,0,0)};
	//create first SVS
	float f1HVS[3] = {0,0,0};
	//create entities
	this->list.push_back(new HELI(v1SVS,f1HVS)); //0
	this->list.push_back(new HELI(v2SVS,f1HVS)); //1
	this->list.push_back(new HELI(v3SVS,f1HVS)); //2

	//SECOND SQUADRON
	//create secondary SVS & HVS
	VEC v6SVS[5]  = {VEC(-10,-150,-100,1),VEC(0,0,1,0),VEC(0,1,0,0), VEC(0,0,0,0), VEC(0,0,0,0)};
	VEC v7SVS[5]  = {VEC(  0,-150,-100,1),VEC(0,0,1,0),VEC(0,1,0,0), VEC(0,0,0,0), VEC(0,0,0,0)};
	VEC v8SVS[5]  = {VEC( 10,-150,-100,1),VEC(0,0,1,0),VEC(0,1,0,0), VEC(0,0,0,0), VEC(0,0,0,0)};
	//create second HVS
	float f2HVS[3] = {90,0,0};
	//create entities
	this->list.push_back(new HELI(v6SVS,f2HVS)); //5
	this->list.push_back(new HELI(v7SVS,f2HVS)); //6
	this->list.push_back(new HELI(v8SVS,f2HVS)); //7

	//set camera target
	this->iCameraTargetValue = 0;
	//set control target
	this->iControlTargetValue = 0;

	return true;
}

bool EntitySet::Release()
{
	//delete list
	for (int i = 0; i < this->GetNumberOfEntities(); i++)
	{
		delete this->list.at(i);
	}

	return true;
}

//accessors
const CAM& EntitySet::GetCAM() const
{
	return this->cam;
}

const deque<EE*>& EntitySet::GetList() const
{
	return this->list;
}

const EE* EntitySet::GetCameraTargetRef() const
{
	return this->list.at(this->iCameraTargetValue);
}

const EE* EntitySet::GetControlTargetRef() const
{
	return this->list.at(this->iControlTargetValue);
}

int EntitySet::GetNumberOfEntities() const
{
	return this->list.size();
}

int EntitySet::GetCameraTargetID() const
{
	return this->iCameraTargetValue;
}

int EntitySet::GetControlTargetID() const
{
	return this->iControlTargetValue;
}

bool EntitySet::CycleCameraTargetUp()
{
	if ( this->iCameraTargetValue < this->list.size()-1 )
	{
		this->iCameraTargetValue++;
	}
	else
	{
		this->iCameraTargetValue = 0;
	}
	return true;
}

bool EntitySet::CycleCameraTargetDown()
{
	if ( this->iCameraTargetValue > 0 )
	{
		this->iCameraTargetValue--;
	}
	else
	{
		this->iCameraTargetValue = this->list.size()-1;
	}
	return true;
}

bool EntitySet::CycleControlTargetUp()
{
	if ( this->iControlTargetValue < this->list.size()-1 )
	{
		this->iControlTargetValue++;
	}
	else
	{
		this->iControlTargetValue = 0;
	}
	return true;
}

bool EntitySet::CycleControlTargetDown()
{
	if ( this->iControlTargetValue > 0 )
	{
		this->iControlTargetValue--;
	}
	else
	{
		this->iControlTargetValue = this->list.size()-1;
	}
	return true;
}

bool EntitySet::AddToList(EE* ee_ptr)
{
	this->list.push_back(ee_ptr);
	return true;
}

bool EntitySet::RemoveFromList(int i)
{

	return false;
}

