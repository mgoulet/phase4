/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//Console.h
/////////////////////////////////////////////////////////////////

#ifndef CONSOLE_H
#define CONSOLE_H

//general includes
#include <iostream>
#include <windows.h>
#include "Glee.h"
#include <gl/glu.h>
#include <deque>
#include <string>
#include <sstream>
using std::string;
using std::istringstream;
using std::deque;
#include "SubComponent.h"
#include "GLCustomLib.h"
using namespace GLCustomLib;

//class definitions
#include "KernelSettings.h"
#include "GameSettings.h"
#include "InputManager.h"
#include "FontManager.h"
#include "TextureSet.h"
#include "GLCustomLib.h"
#include "Timer.h"

//class definition
class Console: public SubComponent
{
public:
	//constructors/destructor
	Console();
	~Console();

	bool AppendToConsole(string str);
	bool ProcessCurrentConsoleMessage(	KernelSettings& kernelsettings_ref,
										GameSettings& gamesettings_ref,
										int fwKeys_down);
	//render console
	bool RenderConsole(	const KernelSettings& kernelsettings_ref,
						const TextureSet& textureset_ref,
						const FontManager& fontmanager_ref,
						const Timer& timer_ref) const;

	//accessors
	const deque<string>& GetMessageList() const;
	const string& GetCurrentMessage() const;

private:

	bool Init();
	bool Release();

	//list of strings to hold past log of crap & commands.
	deque<string> messagelist;
	string currentmessage;

	//private methods for console management
	bool ProcessConsoleCommand(	KernelSettings& kernelsettings_ref,
								GameSettings& gamesettings_ref);
	bool ClearConsole();

};

#endif CONSOLE_H