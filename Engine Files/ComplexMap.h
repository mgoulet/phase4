//////////////////////////////////////////
//author: martin goulet
//CmoplexMap.h
//////////////////////////////////////////

#ifndef COMPLEXMAP_H
#define COMPLEXMAP_H

//includes
#include "SubComponent.h"
#include "EngineMechanics.h"
#include "EngineEntities.h"
#include "Glee.h"
#include "TextureSet.h"
#include "SettingsSubSet.h"
#include "Console.h"
#include "ModelSet.h"
//...

//class declaration
class ComplexMap: public SubComponent
{
public:
	//constructors/destructor
	ComplexMap();
	~ComplexMap();

	bool RenderComplexMap(	const SettingsSubSet& sss_ref,
							const TextureSet& textureset_ref,
							Console& console_ref,
							ModelSet& modelset_ref,
							const CAM& cam_ref) const;

private:
	//init release methods
	bool Init();
	bool Release();

    bool RenderBuilding(float fxbase, float fybase, float fzbase,  float fw, float fh) const;
	bool RenderBuildingSet() const;
	bool RenderPad(float fx, float fy, float fz) const;
	bool RenderCube(float fx, float fy, float fz, float fd) const;
	bool RenderPlatform(float fx, float fy, float fz, float fd, float fh) const;
	//both pos and neg pyramids
	bool RenderHyperPyramid(float fx, float fy, float fz) const;
	//complete upright pyramid
	bool RenderPyramid(float fx, float fy, float fz) const;
	bool RenderPyramidStep(float fx, float fy, float fz, float fd) const;
	bool RenderPyramidTip(float fx, float fy, float fz) const;
	bool RenderAntiPyramid(float fx, float fy, float fz) const;
   	bool RenderAntiPyramidStep(float fx, float fy, float fz, float fd) const;
	bool RenderAntiPyramidTip(float fx, float fy, float fz) const;
	//complete neg pyramid
	bool RenderNegPyramid(float fx, float fy, float fz) const;
	bool RenderNegPyramidStep(float fx, float fy, float fz, float fd) const;
	bool RenderNegPyramidTip(float fx, float fy, float fz) const;
	bool RenderNegAntiPyramid(float fx, float fy, float fz) const;
   	bool RenderNegAntiPyramidStep(float fx, float fy, float fz, float fd) const;
	bool RenderNegAntiPyramidTip(float fx, float fy, float fz) const;

};

#endif COMPLEXMAP_H