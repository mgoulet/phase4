/////////////////////////////////////////////////////////////////
//author: martin goulet
//AssetSet.h
/////////////////////////////////////////////////////////////////

#ifndef ASSETSET_H
#define ASSETSET_H

#include "SubComponent.h"

class AssetSet: public SubComponent
{
public:
	//constructors/destructor
	AssetSet() {}
	~AssetSet() {}

	//pure virtual method, abstracting the class
	virtual bool LoadAssets() = 0;

private:
	//...

};


#endif ASSETSET_H

