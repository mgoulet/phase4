/////////////////////////////////////////////////////////////////
//author: martin goulet
//TextureSet.cpp
/////////////////////////////////////////////////////////////////

#include "TextureSet.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

TextureSet::TextureSet()
{
	//init class memebers
	this->Init();
}

TextureSet::~TextureSet()
{
	//release class members
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

const GLuint* TextureSet::GetTextureIndices() const
{
	return this->textureindices;
}

bool TextureSet::Init()
{
	return true;
}

bool TextureSet::Release()
{
	glDeleteTextures(10, this->textureindices);

	return true;
}

//load asset
bool TextureSet::LoadAssets()
{
	//here the appropriate assets will be loaded
	
	//generate a texture
	glGenTextures(10, this->textureindices);

	/////////////////////////////////////////////////////////////////////
	//FIRST TEXTURE (CONSOLE TEXTURE)
	CTargaImage consoleimage;
	consoleimage.Load("data\\textures\\brick.tga");
	glBindTexture(GL_TEXTURE_2D, this->textureindices[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, consoleimage.GetWidth(), consoleimage.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, consoleimage.GetImage());
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/////////////////////////////////////////////////////////////////////
	//SECOND TEXTURE (SKYSPHERE TEXTURE)
	//create and load a texture
	CTargaImage skyimage;
	skyimage.Load("data\\textures\\nicesky.tga");
	//generate a texture
	glBindTexture(GL_TEXTURE_2D, this->GetTextureIndices()[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, skyimage.GetWidth(), skyimage.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, skyimage.GetImage());
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/////////////////////////////////////////////////////////////////////
	//THIRD TEXTURE (GRASS TEXTURE)
	//create and load a texture
	CTargaImage grassimage;
	grassimage.Load("data\\textures\\grass2.tga");
	//generate a texture
	glBindTexture(GL_TEXTURE_2D, this->GetTextureIndices()[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, grassimage.GetWidth(), grassimage.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, grassimage.GetImage());
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/////////////////////////////////////////////////////////////////////
	//FIRTH TEXTURE (WATER TEXTURE)
	//create and load a texture
	CTargaImage waterimage;
	waterimage.Load("data\\textures\\water.tga");
	//generate a texture
	glBindTexture(GL_TEXTURE_2D, this->GetTextureIndices()[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, waterimage.GetWidth(), waterimage.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, waterimage.GetImage());
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/////////////////////////////////////////////////////////////////////
	//FIFTH TEXTURE
	//create and load a texture
	CTargaImage buildingimage;
	buildingimage.Load("data\\textures\\building.tga");
	//generate a texture
	glBindTexture(GL_TEXTURE_2D, this->GetTextureIndices()[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, buildingimage.GetWidth(), buildingimage.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, buildingimage.GetImage());
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/////////////////////////////////////////////////////////////////////
	//SIXTH TEXTURE (TEMPLE TILE))
	//create and load a texture
	CTargaImage templetile;
	templetile.Load("data\\textures\\tile1.tga");
	//generate a texture
	glBindTexture(GL_TEXTURE_2D, this->GetTextureIndices()[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, templetile.GetWidth(), templetile.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, templetile.GetImage());
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/////////////////////////////////////////////////////////////////////
	return true;
}




