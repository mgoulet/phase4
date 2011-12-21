/////////////////////////////////////////////////////////////////
//author: martin goulet
//HeadsUpDisplay.cpp
/////////////////////////////////////////////////////////////////

#include "HeadsUpDisplay.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

HeadsUpDisplay::HeadsUpDisplay()
{
	//empty for now
}

HeadsUpDisplay::~HeadsUpDisplay()
{
	//empty for now
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool HeadsUpDisplay::RenderHUD(const FontManager& fontmanager_ref, const EntitySet& entityset_ref, const KernelSettings kernelsettings_ref) const
{
	//select modelview
	glMatrixMode(GL_MODELVIEW);
	//push matrix
	glPushMatrix();
	//push attrib
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//load identity
	glLoadIdentity();

	//selection of projection matrix
	glMatrixMode(GL_PROJECTION);
	//push/save current projection matrix
	glPushMatrix();
	//reset our new/current copy
	glLoadIdentity();
	//setup orthogonal projection (parallel)
	glOrtho(0.0f, kernelsettings_ref.iAppWidth, kernelsettings_ref.iAppHeight, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	//enable blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//DRAW HUDS
	this->DrawHuds(fontmanager_ref,entityset_ref, kernelsettings_ref);

	//DISPLAY CAMERA & CONTROL DATA
	this->DisplayCameraAndControlInfo(fontmanager_ref,entityset_ref, kernelsettings_ref);

	//DRAW HYPER RADAR
	this->DrawHyperRadar(fontmanager_ref, entityset_ref, kernelsettings_ref);

	//DRAW CROSSHAIR
	this->DrawCrossHair(kernelsettings_ref);

	glEnable(GL_DEPTH_TEST);
	//pop attrib
	glPopAttrib();
	//pop projection matrix back
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//pop modelview matrix back
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	return true;
}

bool HeadsUpDisplay::DrawHuds(const FontManager& fontmanager_ref, const EntitySet& entityset_ref, const KernelSettings kernelsettings_ref) const
{
	//set main HUD color
	glColor4f(0.2,0.4,0.6,0.7);
	//DRAW TOP HUD
	glRectf(0,0,kernelsettings_ref.iAppWidth,50);
	//DRAW BOTTOM HUD
	//draw rectangle
	glRectf(0, kernelsettings_ref.iAppHeight-50,
			kernelsettings_ref.iAppWidth, kernelsettings_ref.iAppHeight);

	//DRAW HUD DELIMITERS
	//select HUD border color
	glColor4f(0.0,0.0,0.0,0.5);
	glRectf(0,50,kernelsettings_ref.iAppWidth,55);
	glRectf(0,kernelsettings_ref.iAppHeight-55,kernelsettings_ref.iAppWidth,kernelsettings_ref.iAppHeight-50);
	return true;
}

bool HeadsUpDisplay::DisplayCameraAndControlInfo(const FontManager& fontmanager_ref, const EntitySet& entityset_ref, const KernelSettings kernelsettings_ref) const
{
	//display entity number in lower half of HUD
	stringstream ss1;
	string s1,s2;
	ss1 << entityset_ref.GetControlTargetID();
	ss1 >> s1;
	s2 = "Entity Control: " + s1;
	fontmanager_ref.RenderText(s2.c_str(),10,kernelsettings_ref.iAppHeight-10,kernelsettings_ref);
	
	//display entity number in lower half of HUD
	stringstream ss2;
	s1 = "";
	s2 = "";
	//display camera source in lower half of HUD
	ss2 << entityset_ref.GetCameraTargetID();
	ss2 >> s1;
	s2 = "Camera Source: " + s1;
	fontmanager_ref.RenderText(s2.c_str(),10,kernelsettings_ref.iAppHeight-25,kernelsettings_ref);

	stringstream ss3;
	s1 = "";
	s2 = "";
	//display hyperfactor of control entity
	ss3 << entityset_ref.GetControlTargetRef()->fHVS[0];
//	ss3 << MathManipulations::SizVEC(entityset_ref.GetControlTargetRef()->vSVS[3]);
	ss3 >> s1;
	s2 = "HyperFactor: " + s1;
	fontmanager_ref.RenderText(s2.c_str(),200,kernelsettings_ref.iAppHeight-25,kernelsettings_ref);
//	fontmanager_ref.RenderText(s2.c_str(),200,kernelsettings_ref.iAppHeight-25,kernelsettings_ref);

	//Redner User Info
	fontmanager_ref.RenderText("Martin Goulet - Copyright 2005", 770,15,kernelsettings_ref);
	fontmanager_ref.RenderText("mart_goulet@hotmail.com", 825,30,kernelsettings_ref);

	return true;
}

bool  HeadsUpDisplay::DrawHyperRadar(const FontManager&fontmanager_ref,
									 const EntitySet& entityset_ref,
									 const KernelSettings& kernelsettings_ref) const
{
	float fx = kernelsettings_ref.iAppWidth/2;
	float fy = kernelsettings_ref.iAppHeight/2;

	glPushMatrix();
	//draw radar circle
	glLineWidth(3);
	glColor4f(1,0,0,0.5);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i < 360; i+=5)
	{
		float degInRad = i*DEG2RAD;
		glVertex2f(cos(degInRad)*RADAR_RADIUS+fx,sin(degInRad)*RADAR_RADIUS+fy);
	}
	glEnd();

	//draw entities on radar
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int i = 0; i < entityset_ref.GetList().size(); i++)
	{
		float fHyper = entityset_ref.GetList().at(i)->fHVS[0];
		float degInRada = fHyper*DEG2RAD;
		if (entityset_ref.GetList().at(i)->iType < 20)
		{
			glColor4f(0,1,1,0.5);
		}
		else
		{
			glColor4f(1,0,0,0.5);
		}
		glVertex2f(cos(degInRada)*RADAR_RADIUS+fx,sin(degInRada)*RADAR_RADIUS+fy);
	}
	glEnd();

	glPopMatrix();

	//return true
	return true;
}

bool HeadsUpDisplay::DrawCrossHair(const KernelSettings& kernelsettings_ref) const
{
	const float fx = kernelsettings_ref.iAppWidth/2;
	const float fy = kernelsettings_ref.iAppHeight/2;

	glLineWidth(2);

	//drawing cross
	glPushMatrix();
	glColor4f(1,1,1,1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(fx, fy-5);
		glVertex2f(fx, fy+5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(fx-5, fy);
		glVertex2f(fx+5, fy);
	glEnd();
	glPopMatrix();

	return true;
}


