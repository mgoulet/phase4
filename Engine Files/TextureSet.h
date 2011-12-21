/////////////////////////////////////////////////////////////////
//author: martin goulet
//TextureSet.h
/////////////////////////////////////////////////////////////////

#ifndef TEXTURESET_H
#define TEXTURESET_H

//includes
#include "AssetSet.h"
#include "CTargaImage.h"
#include "Glee.h"
#include <gl\glu.h>

//class definition
class TextureSet: public AssetSet
{
public:
	TextureSet();
	~TextureSet();

	//accessor
	const GLuint* GetTextureIndices() const;

	bool LoadAssets();

private:

	//init/release methods
	bool Init();
	bool Release();

	//member variables
	GLuint textureindices[10];

};


#endif TEXTURESET_H