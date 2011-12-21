//////////////////////////////////////////
//author: martin goulet
//HeightMap.cpp
//////////////////////////////////////////

#include "HeightMap.h"



//////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
//////////////////////////////////////////

HeightMap::HeightMap()
{
	this->Init();
}


HeightMap::HeightMap(const HeightMap& heightmap_ref)
{
	//empty for now
}

HeightMap::~HeightMap()
{
	this->Release();
}

//////////////////////////////////////////
//METHODS
//////////////////////////////////////////

bool HeightMap::Init()
{
	//open file
	FILE* file_ptr = fopen("data\\heightmaps\\heightmap.raw", "rb");
	//success check
	if (!file_ptr) return false;
	//read data
	fread(&this->heightmapdata, TERRAIN_SIZE*TERRAIN_SIZE,1,file_ptr);
	//close file
	fclose(file_ptr);

	return true;
}

bool HeightMap::Release()
{
	return true;
}

bool HeightMap::RenderHeightMap(const SettingsSubSet& settingssubset_ref,
								const TextureSet& textureset_ref,
								Console& console_ref,
								const CAM& c_ref) const
{
	//save previous matrix
	glPushMatrix();
	//clean matrix
	glLoadIdentity();
	//save attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//enable other stuff
	glEnable(GL_TEXTURE_2D);

	//ROTATE CAMERA WITHOUT TRANSLATIONS
	gluLookAt( c_ref.vSVS[0].fCoords[0], c_ref.vSVS[0].fCoords[1],c_ref.vSVS[0].fCoords[2],
	c_ref.vSVS[1].fCoords[0]+c_ref.vSVS[0].fCoords[0], c_ref.vSVS[1].fCoords[1]+c_ref.vSVS[0].fCoords[1], c_ref.vSVS[1].fCoords[2]+c_ref.vSVS[0].fCoords[2],
	c_ref.vSVS[2].fCoords[0], c_ref.vSVS[2].fCoords[1], c_ref.vSVS[2].fCoords[2]);

	glTranslatef(0,-300,0);

	//render terrain
	this->RenderTerrain(settingssubset_ref,textureset_ref,console_ref, c_ref);

	//render water
	this->RenderWater(settingssubset_ref,textureset_ref,console_ref, c_ref);

	//pop gl attributes
	glPopAttrib();
	//pop gl matrix
	glPopMatrix();

	return true;
}

bool HeightMap::RenderTerrain(	const SettingsSubSet& sss_ref,
								const TextureSet& textureset_ref,
								Console& console_ref,
								const CAM& cam_ref) const
{
	glBindTexture(GL_TEXTURE_2D, textureset_ref.GetTextureIndices()[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable (GL_DEPTH_TEST);

	glTranslatef(0,-50,0);
	glScalef(TOTAL_SCALE,TOTAL_SCALE,TOTAL_SCALE);
	//texture scale
	int iT = TEXTURE_SCALE;
	//rendering loops for terrain
	for (int z = 1; z < TERRAIN_SIZE - 1; z+=iC)
	{
		glBegin(GL_TRIANGLE_STRIP);
//		glBegin(GL_LINE_STRIP);
		for (int x = 1; x < TERRAIN_SIZE; x+=iC)
		{
			// render two vertices of the strip at once
			float scaledHeight = heightmapdata[z * TERRAIN_SIZE + x] / SCALE_FACTOR;
			float nextScaledHeight = heightmapdata[(z + iC)* TERRAIN_SIZE + x] / SCALE_FACTOR;
			float color = 0.5f + 0.5f * scaledHeight / MAX_HEIGHT;
			float nextColor = 0.5f + 0.5f * nextScaledHeight / MAX_HEIGHT;

			glColor3f(color, color, color);
			glTexCoord2f((GLfloat)x/TERRAIN_SIZE*iT, (GLfloat)z/TERRAIN_SIZE*iT);
			glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE/2), scaledHeight, static_cast<GLfloat>(z - TERRAIN_SIZE/2));

			glColor3f(nextColor, nextColor, nextColor);
			glTexCoord2f((GLfloat)x/TERRAIN_SIZE*iT, (GLfloat)(z+iC)/TERRAIN_SIZE*iT);
			glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE/2), nextScaledHeight, static_cast<GLfloat>(z + iC - TERRAIN_SIZE/2));
		}
		glEnd();

	}

	return true;
}

bool HeightMap::RenderWater(	const SettingsSubSet& sss_ref,
								const TextureSet& textureset_ref,
								Console& console_ref,
								const CAM& cam_ref) const
{	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

	glBindTexture(GL_TEXTURE_2D, textureset_ref.GetTextureIndices()[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//draw the water
	float iM = 1.0f;
	float iT = TEXTURE_SCALE/25;
	glColor4f(1,1,1,0.5);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-TERRAIN_SIZE/2.1f*iM, WATER_HEIGHT, TERRAIN_SIZE/2.1f*iM);

		glTexCoord2f(TERRAIN_SIZE*iT, 0.0);
		glVertex3f(TERRAIN_SIZE/2.1f*iM, WATER_HEIGHT, TERRAIN_SIZE/2.1f*iM);

		glTexCoord2f(TERRAIN_SIZE*iT, TERRAIN_SIZE*iT);
		glVertex3f(TERRAIN_SIZE/2.1f*iM, WATER_HEIGHT, -TERRAIN_SIZE/2.1f*iM);

		glTexCoord2f(0.0, TERRAIN_SIZE*iT);
		glVertex3f(-TERRAIN_SIZE/2.1f*iM, WATER_HEIGHT, -TERRAIN_SIZE/2.1f*iM);
	glEnd();

	return true;
}



