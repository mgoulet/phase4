/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//GameSubComponent.h
/////////////////////////////////////////////////////////////////

#ifndef GAMESUBCOMPONENT_H
#define GAMESUBCOMPONENT_H

class GameSubComponent
{
public:

	//constructors/destructor
	GameSubComponent() {}
	~GameSubComponent() {}

private:

	//abstract methods
	bool virtual Init() = 0;
	bool virtual Release() = 0;

};

#endif GAMESUBCOMPONENT_H