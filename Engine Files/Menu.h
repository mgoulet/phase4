/////////////////////////////////////////////////////////////////
//author: martin goulet
//Menu.h
/////////////////////////////////////////////////////////////////

#ifndef MENU_H
#define MENU_H

//includes
#include <iostream>
#include <deque>
#include <string>
using std::deque;
using std::string;

#include "SubComponent.h"

class Menu: public SubComponent
{
public:
	//constructors/destructor
	Menu();
	~Menu();

	//accessors
	int GetCurrentPosition() const;
	const deque<string>& GetMenuList() const;

	bool MoveUp();
	bool MoveDown();

private:

	//init/release methods
	bool Init();
	bool Release();

	//current menu position
	int iCurrentPosition;

	//private members
	deque<string> menulist;


};

#endif MENU_H