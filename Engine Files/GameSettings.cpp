/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//GameSettings.h
/////////////////////////////////////////////////////////////////

#include "GameSettings.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

GameSettings::GameSettings()
{
	//init class
	this->Init();
}

GameSettings::~GameSettings()
{
	//release class
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool GameSettings::Init()
{
	this->hud = true;

	return true;
}

bool GameSettings::Release()
{
	return true;
}