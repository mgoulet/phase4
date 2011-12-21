//////////////////////////////////////////
//author: martin goulet
//FPSCounter.cpp
//////////////////////////////////////////

#include "FPSCounter.h"

extern HDC hDC;

//////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
//////////////////////////////////////////

FPSCounter::FPSCounter()
{
	//init class members
	this->Init();

}

FPSCounter::~FPSCounter()
{
	//release class members
	this->Release();

}

//////////////////////////////////////////
//METHODS
//////////////////////////////////////////

bool FPSCounter::Init()
{
	//init fps data
	this->iframecount = 0;
	this->flasttime = /*this->td_ptr->GetTime() * */0.001f;

	return true;
}

bool FPSCounter::Release()
{
	return true;
}

char* FPSCounter::GetFPS(const Timer& timer_ref) const
{
	//increment number of calls to this method
	this->iframecount++;
	//get time
	float fnewtime = timer_ref.GetTime() * 0.001f;

	if ( (fnewtime - this->flasttime) > 0.5 )
	{	//need to update

		//compute fps
		float fFPS = this->iframecount / (fnewtime - this->flasttime);
		//reset frame count
		this->iframecount = 0;
		//store last fps value
		this->flastfps = fFPS;
		//rewnew lasttime
		this->flasttime = fnewtime;

		//create a textstring to render
		char* textstring = "FPS: %.2f";

		/////////////////////////////////////////
		//RENDER fFPS !!!
		this->CreateOutputString(output, "FPS: %.2f", fFPS);
		/////////////////////////////////////////

	}
	else
	{	//no update needed

		//create a textstring to render
		char* textstring = "FPS: %.2f";

		/////////////////////////////////////////
		//RENDER flastfps !!!
		this->CreateOutputString(output, "FPS: %.2f", flastfps);
		/////////////////////////////////////////
	}

	//return "FPS!!!";
	return this->output;
}

bool FPSCounter::CreateOutputString(char* output, char* input, ...) const
{
	//merge stuff
	va_list va;
	va_start(va, input);
	vsprintf(output, input, va);
	va_end(va);

	return true;
}

bool FPSCounter::RenderFPS(const Timer& timer_ref,
						   const FontManager& fontmanager_ref,
						   const KernelSettings& kernelsettings_ref) const
{
	
	glPushMatrix();

	//get actual favlue to display
	char* output = this->GetFPS(timer_ref);
	//call to fontmanager to render FPS text
	fontmanager_ref.RenderText(output, 2, 12, kernelsettings_ref);

	glPopMatrix();
	
	return true;
}

