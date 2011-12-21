/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//SubComponent.h
/////////////////////////////////////////////////////////////////

#ifndef SUBCOMPONENT_H
#define SUBCOMPONENT_H

class SubComponent
{
public:

	//constructors/destructor
	SubComponent() {}
	~SubComponent() {}

private:

	//abstract methods
	bool virtual Init() = 0;
	bool virtual Release() = 0;

};

#endif SUBCOMPONENT_H