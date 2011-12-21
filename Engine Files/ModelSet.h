/////////////////////////////////////////////////////////////////
//author: martin goulet
//ModelSet.h
/////////////////////////////////////////////////////////////////

#ifndef MODELSET_H
#define MODELSET_H

//includes
#include <iostream> 
#include <string>
#include <deque>
#include "AssetSet.h"
#include "MD2.h"
#include "EngineMechanics.h"
#include "EngineEntities.h"
using std::string;
using std::deque;

class ModelSet: public AssetSet
{
public:
	ModelSet();
	~ModelSet();

	//polymorphic method
	bool LoadAssets();

	const deque<CMD2Model>& GetModelList() const;
	const CMD2Model& GetModelAt(int i) const;

private:

	//init/release methods
	bool Init();
	bool Release();

	//other methods and members
	deque<CMD2Model> modellist;

};

#endif CMD2ModelSET_H