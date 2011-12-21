/////////////////////////////////////////////////////////////////
//author: martin goulet
//ModelSet.cpp
/////////////////////////////////////////////////////////////////

#include "ModelSet.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

ModelSet::ModelSet()
{
	//init
	this->Init();
}

ModelSet::~ModelSet()
{
	//release
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool ModelSet::Init()
{
	return true;
}

bool ModelSet::Release()
{
	return true;
}

bool ModelSet::LoadAssets()
{
	//load stuff

	//push a model
	this->modellist.push_back(CMD2Model());
	//attempting to load a md2 model
	if (!this->modellist.at(0).Load("data\\models\\airwolf.md2","data\\textures\\airwolf.tga",0.2f)) return false;	
	//push a second model
	this->modellist.push_back(CMD2Model());
	//attempting to load a md2 model
	if (!this->modellist.at(1).Load("data\\models\\rocket1.md2","data\\textures\\rocket1.tga",0.05f)) return false;
	//push a third model
	this->modellist.push_back(CMD2Model());
	if (!this->modellist.at(2).Load("data\\models\\rhino1.md2","data\\textures\\rhino1.tga",0.2f)) return false;
	//push a fourth model
	this->modellist.push_back(CMD2Model());
	if (!this->modellist.at(3).Load("data\\models\\void.md2","data\\textures\\tile1.tga",2.0f)) return false;

	//success
	return true;
}

const deque<CMD2Model>& ModelSet::GetModelList() const
{
	return this->modellist;
}

const CMD2Model& ModelSet::GetModelAt(int i) const
{
	/*
	if ( (i>=0) && (i < this->modellist.size()) )
	{
		return this->modellist.at(i);
	}
	else
	{
		//fire error
		int i = 0;
		int j = 4 / i;
		return this->modellist.at(i);
	}
	*/
	return this->modellist.at(i);
}

