/////////////////////////////////////////////////////////////////
//Author: mg goulet
//Project: phase4
//Console.cpp
/////////////////////////////////////////////////////////////////

#include "Console.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

Console::Console()
{
	//init class
	this->Init();
}

Console::~Console()
{
	//release class
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool Console::AppendToConsole(string str)
{
	this->messagelist.push_front(str);

	return true;
}

bool Console::ProcessCurrentConsoleMessage(KernelSettings& kernelsettings_ref,
										   GameSettings& gamesettings_ref,
										   int fwKeys_down)
{
	//if ENTER, then put in queue and clear current message
	if (fwKeys_down == 13)
	{
		//add message to console list to be displayed
		this->AppendToConsole(this->currentmessage);

		if (this->currentmessage != "")
		{
			//process command
			this->ProcessConsoleCommand(kernelsettings_ref,gamesettings_ref);
		}

		//clear current message
		this->currentmessage.resize(0);
	}
	//if numeric, add to string
	if ( (fwKeys_down >= 48) && (fwKeys_down <=57) )
	{
		this->currentmessage+=fwKeys_down;
	}
	//if alpha character, apend lowercase version (+32)
	if ( (fwKeys_down >=65) && (fwKeys_down<=90) )
	{
		this->currentmessage+=fwKeys_down+32;
	}
	
	//deal with special characters such as space and backspace
	switch(fwKeys_down)
	{
	case VK_SPACE:
		this->currentmessage+=" ";
		break;
	case VK_BACK:
		if (this->currentmessage.size()>0)
		{
			this->currentmessage.resize(this->currentmessage.size()-1);
		}
		break;
	default:
		break;
	}

	//resize message to maximum size if exceeded
	if (this->currentmessage.size() > 50)
	{
		this->currentmessage.resize(this->currentmessage.size()-1);
	}
	
	return true;
}

bool Console::ProcessConsoleCommand(KernelSettings& kernelsettings_ref,
							GameSettings& gamesettings_ref)
{
/*
std::string token, text("Here:is:some:text");
   std::istringstream iss(text);
   while ( getline(iss, token, ':') )
   {
      std::cout << token << std::endl;
   }
*/

	istringstream iss(this->currentmessage);

	//NULL MESSAGE
	if (this->currentmessage == "")
	{
		return true;
	}

	//ERROR MESSAGE
	if (this->currentmessage == "ERROR")
	{
		//error message if this is reached
		this->AppendToConsole("ERROR IN COMMAND PUMP");
		return true;
	}

	//QUIT/EXIT command
	if ( (this->currentmessage == "quit") || (this->currentmessage == "exit") )
	{
		//activate quit message
		kernelsettings_ref.exit = true;
		return true;
	}
	//CLEAR COMMAND
	if (this->currentmessage == "clear")
	{
		this->messagelist.resize(0);
		return true;
	}
	/*
	//FOV COMMAND
	if (this->currentmessage == "fov")
	{
		kernelsettings_ref.exit = true;
	}
	*/
	//MODELS3D
	if (this->currentmessage == "models3d")
	{
		kernelsettings_ref.models3d = !kernelsettings_ref.models3d;
		return true;
	}
	//MATH3D
	if (this->currentmessage == "math3d")
	{
		kernelsettings_ref.math3d = !kernelsettings_ref.math3d;
		return true;
	}
	//SKYSPHERE COMMAND
	if (this->currentmessage == "skysphere")
	{
		kernelsettings_ref.skysphere = !kernelsettings_ref.skysphere;
		return true;
	}

	//WHATEV COMMAND
	//at this point, command was invalid
	this->AppendToConsole("Invalid Command: " + this->currentmessage);
	return true;
}

//accessors
const deque<string>& Console::GetMessageList() const
{
	return this->messagelist;
}

const string& Console::GetCurrentMessage() const
{
	return this->currentmessage;
}


bool Console::Init()
{
	//init curent string to nothing
	this->currentmessage = "";

	return true;
}

bool Console::Release()
{
	//release clas members
	return true;
}

bool Console::ClearConsole()
{
	//delete current message AND messagelist.
	this->currentmessage = "";
	this->messagelist.resize(0);

	return true;
}

bool Console::RenderConsole(const KernelSettings& kernelsettings_ref,
							const TextureSet& textureset_ref,
							const FontManager& fontmanager_ref,
							const Timer& timer_ref) const
{
	//selection of projection matrix
	glMatrixMode(GL_PROJECTION);
	//push/save current projection matrix
	glPushMatrix();
	//reset our new/current copy
	glLoadIdentity();
	//setup orthogonal projection (parallel)
	glOrtho(0.0f, kernelsettings_ref.iAppWidth, kernelsettings_ref.iAppHeight, 0.0f, -1.0f, 1.0f);
	//select modelview
	
	glMatrixMode(GL_MODELVIEW);
	//save matrix
	glPushMatrix();
	//reset it
	glLoadIdentity();
	//save attribs
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//enable alpha
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	//set color
	glColor4f(kernelsettings_ref.consolesettings[0], kernelsettings_ref.consolesettings[1],
			  kernelsettings_ref.consolesettings[2], kernelsettings_ref.consolesettings[3]);

	//bind console texture
	glBindTexture(GL_TEXTURE_2D, textureset_ref.GetTextureIndices()[0]);
	glEnable(GL_TEXTURE_2D);

	//draw triangle strip consisting console
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0, 1.0);	glVertex2f(0, /*0*/55);
		glTexCoord2f(0.0, 0.0);	glVertex2f(0, kernelsettings_ref.iAppHeight/2);
		glTexCoord2f(2.0, 1.0);	glVertex2f( kernelsettings_ref.iAppWidth, /*0*/55);
		glTexCoord2f(2.0, 0.0);	glVertex2f( (kernelsettings_ref.iAppWidth), kernelsettings_ref.iAppHeight/2);
	glEnd();

	//draw bottom frame (black bottom line)
	glColor4f(0.0, 0.0, 0.0, 0.5);
	glRectf(	0,kernelsettings_ref.iAppHeight/2,
				kernelsettings_ref.iAppWidth, kernelsettings_ref.iAppHeight/2+5);

	//RENDERING MESSAGE LIST
	fontmanager_ref.RenderText("->", 0, (kernelsettings_ref.iAppHeight/2), kernelsettings_ref);
	fontmanager_ref.RenderText(this->GetCurrentMessage().c_str(), 25, (kernelsettings_ref.iAppHeight/2), kernelsettings_ref);
	for (int i = 0; i < this->GetMessageList().size(); i++)
	{
		int iFontSize = kernelsettings_ref.iFontSize;
		fontmanager_ref.RenderText(this->GetMessageList().at(i).c_str(), 0, (kernelsettings_ref.iAppHeight/2) - ( (i+1) * iFontSize), kernelsettings_ref);
		if (i > 8) break;	//break so messages dont go beyond console delimiters
	}

	//disable textures
	glDisable(GL_TEXTURE_2D);
	//disable blend
	glDisable(GL_BLEND);
	//pop attribs
	glPopAttrib();

	//select and pop old projection matrix back
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//select and pop old modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	return true;
}


