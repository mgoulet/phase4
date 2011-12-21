//////////////////////////////////////////
//author: martin goulet
//HeightMap.h
//////////////////////////////////////////

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

//includes
#include <windows.h>
#include <cmath>
#include "Glee.h"
#include <gl/glu.h>
#include "CTargaImage.h"
#include "SettingsSubSet.h"
#include "Console.h"
#include "EngineMechanics.h"
#include "EngineEntities.h"
#include "SubComponent.h"
#include "TextureSet.h"

const int TERRAIN_SIZE = 260;
const float MAX_HEIGHT = 100.0f;
const float MAX_FOG_HEIGHT = MAX_HEIGHT * 0.5f;
const float SCALE_FACTOR = 256.0f / MAX_HEIGHT;
const float TOTAL_SCALE = 5.0f;
const float WATER_HEIGHT = 10.0f;
const float TEXTURE_SCALE = 15.0f;

const int iC = 5; // terrain complexity

//class def
class HeightMap: public SubComponent
{
public:
	HeightMap();
	HeightMap(const HeightMap& heightmap_ref);
	~HeightMap();

	bool RenderHeightMap(	const SettingsSubSet& sss_ref,
							const TextureSet& textureset_ref,
							Console& console_ref,
							const CAM& cam_ref) const;

private:
	GLubyte heightmapdata[TERRAIN_SIZE * TERRAIN_SIZE];

	bool Init();
	bool Release();
	
	bool RenderTerrain(const	SettingsSubSet& sss_ref,
								const TextureSet& textureset_ref,
								Console& console_ref,
								const CAM& cam_ref) const;

	bool RenderWater(const	SettingsSubSet& sss_ref,
							const TextureSet& textureset_ref,
							Console& console_ref,
							const CAM& cam_ref) const;

};


#endif HEIGHTMAP_H

