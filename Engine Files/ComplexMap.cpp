//////////////////////////////////////////
//author: martin goulet
//ComplexMap.cpp
//////////////////////////////////////////

#include "Complexmap.h"

//////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
//////////////////////////////////////////

ComplexMap::ComplexMap()
{
	this->Init();
}

ComplexMap::~ComplexMap()
{
	this->Release();
}

//////////////////////////////////////////
//METHODS
//////////////////////////////////////////

bool ComplexMap::RenderComplexMap(	const SettingsSubSet& sss_ref,
									const TextureSet& textureset_ref,
									Console& console_ref,
									ModelSet& modelset_ref,
									const CAM& c_ref) const
{
	//push/save GL shit
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//ROTATE CAMERA WITHOUT TRANSLATIONS
	gluLookAt( c_ref.vSVS[0].fCoords[0], c_ref.vSVS[0].fCoords[1],c_ref.vSVS[0].fCoords[2],
	c_ref.vSVS[1].fCoords[0]+c_ref.vSVS[0].fCoords[0], c_ref.vSVS[1].fCoords[1]+c_ref.vSVS[0].fCoords[1], c_ref.vSVS[1].fCoords[2]+c_ref.vSVS[0].fCoords[2],
	c_ref.vSVS[2].fCoords[0], c_ref.vSVS[2].fCoords[1], c_ref.vSVS[2].fCoords[2]);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureset_ref.GetTextureIndices()[4]);
	glEnable (GL_DEPTH_TEST);

	//render buildings
	this->RenderBuildingSet();

	//animate black hole
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef(-25, 1000, -25);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	modelset_ref.GetModelAt(3).Animate(0.01);
	modelset_ref.GetModelAt(3).SetAnimationCustom(0,100);
	modelset_ref.GetModelAt(3).Render();
	glPopAttrib();
	glPopMatrix();


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureset_ref.GetTextureIndices()[5]);
	glEnable(GL_DEPTH_TEST);

	//RENDER PYRAMIDS
	for (int i = 0; i < 5; i++)
	{
		//south
		this->RenderHyperPyramid( 1000 - (500* i), 500 - (200 * i), 1000 + (1000*i));
		this->RenderHyperPyramid(-1000 + (500* i), 500 - (200 * i),1000 + (1000*i));
		//east
		this->RenderHyperPyramid( 1000 + (1000*i), 500 - (200 * i), 300);
		this->RenderHyperPyramid( 1000 + (1000*i), 500 - (200 * i), -300);
		//north
		this->RenderHyperPyramid( 1000, 500 - (200 * i), -1000 - (1000*i));
		this->RenderHyperPyramid(-1000, 500 - (200 * i),-1000 - (1000*i));
		//west
		this->RenderHyperPyramid( -1000 - (1000*i), 500 - (200 * i), 300);
		this->RenderHyperPyramid( -1000 - (1000*i), 500 - (200 * i), -300);
		//four corners
		/*
		this->RenderHyperPyramid( 1000 + (1000*i), 800, -1000 - (1000*i));
		this->RenderHyperPyramid( 1000 + (1000*i), 800, 1000 + (1000*i));
		this->RenderHyperPyramid( -1000 - (1000*i), 800, 1000 - (1000*i));
		this->RenderHyperPyramid( -1000 - (1000*i), 800, -1000 - (1000*i));
		*/
	}
	/*
	this->RenderHyperPyramid(450, 200, 450);
	this->RenderHyperPyramid(450, 400, 150);
	this->RenderHyperPyramid(450, 100, -250);
	this->RenderHyperPyramid(450, 300, -550);
	*/

	//render pads
	this->RenderPad(-55,-155,5);
	this->RenderPad(-30,-155,5);
	this->RenderPad(-5,-155,5);

	//pop/restore GL shit
	glPopMatrix();
	glPopAttrib();

	return true;
}
bool ComplexMap::RenderBuildingSet() const
{
	//west buildings
	this->RenderBuilding(-1000,-500,0,100,2000);
	this->RenderBuilding(-500,-500,-500,100,3000);
	this->RenderBuilding(-750,-500,-300,100,3000);
	this->RenderBuilding(-1000,-500,300,100,3000);
//	this->RenderBuilding(-1000,-500,-600,50,4000);

	/*
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//render buildings
			this->RenderBuilding((10 * i) + 0.0+0.2f, -50.5f, (10 * j ) + 30.2f, 5.0f, 800.0f);
			this->RenderBuilding((20 * i) + 15+20.2f, -50.5f, (20 * j ) + 0.2f, 5.0f, 1500.0f);
			this->RenderBuilding((30 * i) + 40+40.2f, -50.5f, (30 * j ) - 60.2f, 5.0f, 900.0f);
		}
	}
	*/

	return true;
}

bool ComplexMap::RenderPad(float fx, float fy, float fz) const
{
	glColor4f(0.5,0.5,0.5,1);
	this->RenderPlatform(fx,fy,fz,10,2);

	//render energy stuff
	glColor4f(0.5,0.5,1,0.6);
	for (float f = -2; f > -50; f-=4)
	{
		glColor4f(0.5,0.5,1, 1 + (f/50));
		this->RenderPlatform(fx+3, fy+f, fz-3, 4, 2);
	}

	return true;
}


bool ComplexMap::RenderBuilding(float fxbase, float fybase, float fzbase,  float fw, float fh) const
{
	glPushMatrix();
	glTranslatef(fxbase,fybase,fzbase);
	glColor4f(0.7,0.7,0.7,1);
	//curently perimiter
	glBegin(GL_TRIANGLE_STRIP);
	//first peg
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-fw, 0.0f, fw);
	glTexCoord2f(0.0f, 50.0f);
	glVertex3f(-fw, fh, fw);
	//second peg
	glTexCoord2f(10.0f, 0.0f);
	glVertex3f(-fw, 0.0f, -fw);
	glTexCoord2f(10.0f, 50.0f);
	glVertex3f(-fw, fh, -fw);
	//third peg
	glTexCoord2f(20.0f, 0.0f);
	glVertex3f(fw, 0.0f, -fw);
	glTexCoord2f(20.0f, 50.0f);
	glVertex3f(fw, fh, -fw);
	//fourth peg
	glTexCoord2f(30.0f, 0.0f);
	glVertex3f(fw, 0.0f, fw);
	glTexCoord2f(30.0f, 50.0f);
	glVertex3f(fw, fh, fw);
	//fifth (first peg)
	glTexCoord2f(40.0f, 0.0f);
	glVertex3f(-fw, 0.0f, fw);
	glTexCoord2f(40.0f, 50.0f);
	glVertex3f(-fw, fh, fw); //first top corner
	glEnd();
	//render top
	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-fw, fh, fw);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-fw, fh, -fw);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fw, fh, -fw);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fw, fh, fw);
	glEnd();
	glColor3f(1,1,1);
	glPopMatrix();
	return true;
}

bool ComplexMap::RenderCube(float fx, float fy, float fz, float fd) const
{
	//push
	glPushMatrix();

	//enable face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//move
	glTranslatef(fx,fy,fz);

	glBegin(GL_TRIANGLE_STRIP);
	//first peg
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, fd, 0);
	//second peg
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -fd);
	glTexCoord2f(1, 1);
	glVertex3f(0, fd, -fd);
	//third peg
	glTexCoord2f(2, 0);
	glVertex3f(fd, 0, -fd);
	glTexCoord2f(2, 1);
	glVertex3f(fd, fd, -fd);
	//fourth peg
	glTexCoord2f(3, 0);
	glVertex3f(fd, 0, 0);
	glTexCoord2f(3, 1);
	glVertex3f(fd, fd, 0);
	//fifth (first peg)
	glTexCoord2f(4, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(4, 1);
	glVertex3f(0, fd, 0);
	glEnd();

	//render top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, fd, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fd, fd, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fd, fd, -fd);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, fd, -fd);

	glEnd();

	//render bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, -fd);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fd, 0, -fd);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fd, 0, 0);
	glEnd();

	glDisable(GL_CULL_FACE);

	//pop
	glPopMatrix();

	return true;
}

bool ComplexMap::RenderPlatform(float fx, float fy, float fz, float fd, float fh) const
{
	glPushMatrix();

	//enable face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//move
	glTranslatef(fx,fy,fz);

	glBegin(GL_TRIANGLE_STRIP);
	//first peg
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, fh, 0);
	//second peg
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -fd);
	glTexCoord2f(1, 1);
	glVertex3f(0, fh, -fd);
	//third peg
	glTexCoord2f(2, 0);
	glVertex3f(fd, 0, -fd);
	glTexCoord2f(2, 1);
	glVertex3f(fd, fh, -fd);
	//fourth peg
	glTexCoord2f(3, 0);
	glVertex3f(fd, 0, 0);
	glTexCoord2f(3, 1);
	glVertex3f(fd, fh, 0);
	//fifth (first peg)
	glTexCoord2f(4, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(4, 1);
	glVertex3f(0, fh, 0);
	glEnd();

	//render top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, fh, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fd, fh, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fd, fh, -fd);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, fh, -fd);
	glEnd();

	//render bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, -fd);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fd, 0, -fd);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fd, 0, 0);
	glEnd();

	glDisable(GL_CULL_FACE);

	glPopMatrix();

	return true;
}

bool ComplexMap::RenderHyperPyramid(float fx, float fy, float fz) const
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	//render top
	this->RenderPyramid(fx, fy, fz);
//	this->RenderAntiPyramid(fx, fy, fz);
	//render bottom
//	this->RenderNegPyramid(fx, fy, fz);
	this->RenderNegAntiPyramid(fx, fy, fz);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	

	return true;
}

bool ComplexMap::RenderPyramid(float fx, float fy, float fz) const
{
	//render steps
	glColor4f(0.2,0.2,0.2,1);
	this->RenderPyramidStep(fx, fy, fz, 200);
	glColor4f(1,0,0,0.5);
	this->RenderPyramidStep(fx, fy+40, fz, 160);

	this->RenderPyramidStep(fx, fy+80, fz, 120);

	this->RenderPyramidStep(fx, fy+120, fz, 80);

	this->RenderPyramidStep(fx, fy+160, fz, 40);

	this->RenderPyramidTip(fx, fy+190, fz);

	return true;
}

bool ComplexMap::RenderPyramidStep(float fx, float fy, float fz, float fr) const
{
	glPushMatrix();

	float d = fr/2;
	float slant = 10;
	float height = 20;

	glBegin(GL_TRIANGLE_STRIP);
	//first peg
	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy+height, fz+d-slant);
	//second peg
//	glTexCoord2f(1, 0);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1, 1);
	glVertex3f(fx-d+slant, fy+height, fz-d+slant);
	//third peg
//	glTexCoord2f(2, 0);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(2, 1);
	glVertex3f(fx+d-slant, fy+height, fz-d+slant);
	//fourth peg
//	glTexCoord2f(3, 0);
	glVertex3f(fx+d, fy, fz+d);
//	glTexCoord2f(3, 1);
	glVertex3f(fx+d-slant, fy+height, fz+d-slant);
	//fifth (first peg)
//	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy+height, fz+d-slant);
	glEnd();

	//render top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d+slant, fy+height, fz+d-slant);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d+slant, fy+height, fz-d+slant);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d-slant, fy+height, fz-d+slant);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d-slant, fy+height, fz+d-slant);
	glEnd();

	//render bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d, fy, fz+d);
	glEnd();

	glPopMatrix();

	return true;
}

bool ComplexMap::RenderPyramidTip(float fx, float fy, float fz) const
{
	
	glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx, fy+10, fz);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(fx-5, fy, fz-5);

		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(fx+5, fy, fz-5);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fx+5, fy, fz+5);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

	glEnd();

	return true;
}

bool ComplexMap::RenderAntiPyramid(float fx, float fy, float fz) const
{
	
	//render steps
	glColor4f(0.2,0.2,0.2,1);
	this->RenderAntiPyramidStep(fx, fy, fz, 200);

	glColor4f(1,0,0,0.5);
	this->RenderAntiPyramidStep(fx, fy+40, fz, 160);

	this->RenderAntiPyramidStep(fx, fy+80, fz, 120);

	this->RenderAntiPyramidStep(fx, fy+120, fz, 80);

	this->RenderAntiPyramidStep(fx, fy+160, fz, 40);

	this->RenderAntiPyramidTip(fx, fy+190, fz);

	return true;
}

bool ComplexMap::RenderAntiPyramidStep(float fx, float fy, float fz, float fr) const
{
	glPushMatrix();

	float d = fr/2;
	float slant = 10;
	float height = 20;

	glBegin(GL_TRIANGLE_STRIP);
	//first peg
	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy-height, fz+d-slant);
	//second peg
//	glTexCoord2f(1, 0);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1, 1);
	glVertex3f(fx-d+slant, fy-height, fz-d+slant);
	//third peg
//	glTexCoord2f(2, 0);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(2, 1);
	glVertex3f(fx+d-slant, fy-height, fz-d+slant);
	//fourth peg
//	glTexCoord2f(3, 0);
	glVertex3f(fx+d, fy, fz+d);
//	glTexCoord2f(3, 1);
	glVertex3f(fx+d-slant, fy-height, fz+d-slant);
	//fifth (first peg)
//	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy-height, fz+d-slant);
	glEnd();

	//render bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d+slant, fy-height, fz+d-slant);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d+slant, fy-height, fz-d+slant);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d-slant, fy-height, fz-d+slant);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d-slant, fy-height, fz+d-slant);
	glEnd();

	//render top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d, fy, fz+d);
	glEnd();

	glPopMatrix();

	return true;
}

bool ComplexMap::RenderAntiPyramidTip(float fx, float fy, float fz) const
{
	
	glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx, fy-10, fz);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(fx-5, fy, fz-5);

		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(fx+5, fy, fz-5);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fx+5, fy, fz+5);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

	glEnd();

	return true;
}

////////////////////////////////////////////////
////////////////////////////////////////////////

bool ComplexMap::RenderNegPyramid(float fx, float fy, float fz) const
{
	//render steps
	glColor4f(0.2,0.2,0.2,1);
	this->RenderPyramidStep(fx, fy, fz, 200);

	glColor4f(1,0,0,0.5);
	this->RenderPyramidStep(fx, fy-39, fz, 160);

	this->RenderPyramidStep(fx, fy-79, fz, 120);

	this->RenderPyramidStep(fx, fy-119, fz, 80);

	this->RenderPyramidStep(fx, fy-159, fz, 40);

	this->RenderPyramidTip(fx, fy-189, fz);

	return true;
}

bool ComplexMap::RenderNegPyramidStep(float fx, float fy, float fz, float fr) const
{
	glPushMatrix();

	float d = fr/2;
	float slant = 10;
	float height = 20;

	glBegin(GL_TRIANGLE_STRIP);
	//first peg
	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy+height, fz+d-slant);
	//second peg
//	glTexCoord2f(1, 0);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1, 1);
	glVertex3f(fx-d+slant, fy+height, fz-d+slant);
	//third peg
//	glTexCoord2f(2, 0);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(2, 1);
	glVertex3f(fx+d-slant, fy+height, fz-d+slant);
	//fourth peg
//	glTexCoord2f(3, 0);
	glVertex3f(fx+d, fy, fz+d);
//	glTexCoord2f(3, 1);
	glVertex3f(fx+d-slant, fy+height, fz+d-slant);
	//fifth (first peg)
//	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy+height, fz+d-slant);
	glEnd();

	//render top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d+slant, fy+height, fz+d-slant);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d+slant, fy+height, fz-d+slant);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d-slant, fy+height, fz-d+slant);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d-slant, fy+height, fz+d-slant);
	glEnd();

	//render bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d, fy, fz+d);
	glEnd();

	glPopMatrix();

	return true;
}

bool ComplexMap::RenderNegPyramidTip(float fx, float fy, float fz) const
{
	
	glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx, fy+10, fz);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(fx-5, fy, fz-5);

		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(fx+5, fy, fz-5);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fx+5, fy, fz+5);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

	glEnd();

	return true;
}

bool ComplexMap::RenderNegAntiPyramid(float fx, float fy, float fz) const
{
	
	//render steps
	glColor4f(0.2,0.2,0.2,1);
	this->RenderAntiPyramidStep(fx, fy, fz, 200);

	glColor4f(1,0,0,0.5);
	this->RenderAntiPyramidStep(fx, fy-39, fz, 160);

	this->RenderAntiPyramidStep(fx, fy-79, fz, 120);

	this->RenderAntiPyramidStep(fx, fy-119, fz, 80);

	this->RenderAntiPyramidStep(fx, fy-159, fz, 40);

	this->RenderAntiPyramidTip(fx, fy-189, fz);

	return true;
}

bool ComplexMap::RenderNegAntiPyramidStep(float fx, float fy, float fz, float fr) const
{
	glPushMatrix();

	float d = fr/2;
	float slant = 10;
	float height = 20;

	glBegin(GL_TRIANGLE_STRIP);
	//first peg
	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy-height, fz+d-slant);
	//second peg
//	glTexCoord2f(1, 0);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1, 1);
	glVertex3f(fx-d+slant, fy-height, fz-d+slant);
	//third peg
//	glTexCoord2f(2, 0);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(2, 1);
	glVertex3f(fx+d-slant, fy-height, fz-d+slant);
	//fourth peg
//	glTexCoord2f(3, 0);
	glVertex3f(fx+d, fy, fz+d);
//	glTexCoord2f(3, 1);
	glVertex3f(fx+d-slant, fy-height, fz+d-slant);
	//fifth (first peg)
//	glTexCoord2f(0, 0);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0, 1);
	glVertex3f(fx-d+slant, fy-height, fz+d-slant);
	glEnd();

	//render bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d+slant, fy-height, fz+d-slant);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d+slant, fy-height, fz-d+slant);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d-slant, fy-height, fz-d+slant);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d-slant, fy-height, fz+d-slant);
	glEnd();

	//render top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fx-d, fy, fz+d);
//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fx-d, fy, fz-d);
//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fx+d, fy, fz-d);
//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fx+d, fy, fz+d);
	glEnd();

	glPopMatrix();

	return true;
}

bool ComplexMap::RenderNegAntiPyramidTip(float fx, float fy, float fz) const
{
	
	glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx, fy-10, fz);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(fx-5, fy, fz-5);

		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(fx+5, fy, fz-5);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fx+5, fy, fz+5);

		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(fx-5, fy, fz+5);

	glEnd();

	return true;
}

bool ComplexMap::Init()
{
	//empty for now
	return true;
}

bool ComplexMap::Release()
{
	//empty for now
	return true;
}
