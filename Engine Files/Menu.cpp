/////////////////////////////////////////////////////////////////
//author: martin goulet
//Menu.cpp
/////////////////////////////////////////////////////////////////

#include "Menu.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

Menu::Menu()
{
	//empty
}

Menu::~Menu()
{
	//empty
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

//accessors
int Menu::GetCurrentPosition() const
{
	return this->iCurrentPosition;
}

const deque<string>& Menu::GetMenuList() const
{
	return this->menulist;
}

bool Menu::MoveUp()
{
	if (this->iCurrentPosition >= this->menulist.size()-1)
	{
		//loop back to top menu
		this->iCurrentPosition = 0;
	}
	else
	{
		//increment
		this->iCurrentPosition++;
	}
	return true;	
}

bool Menu::MoveDown()
{
	if (this->iCurrentPosition <= 0)
	{
		//loop back to bottom menu
		this->iCurrentPosition = this->menulist.size()-1;
	}
	else
	{
		//increment
		this->iCurrentPosition--;
	}
	return true;
}

//init/release methods
bool Menu::Init()
{
	//create simple menu
	this->iCurrentPosition = 0;
//	this->menulist.push_front("Start Game");
//	this->menulist.push_front("About...");
//	this->menulist.push_front("Quit");

	return true;
}

bool Menu::Release()
{
	//empty
	return true;
}


