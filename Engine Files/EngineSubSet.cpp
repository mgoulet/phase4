/////////////////////////////////////////////////////////////////
//Author: mg goulet
//EngineSubSet.cpp
/////////////////////////////////////////////////////////////////

#include "EngineSubSet.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

EngineSubSet::EngineSubSet()
{
	//empty
}

EngineSubSet::~EngineSubSet()
{
	//empty
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

//const accessors
const Timer& EngineSubSet::GetTimer() const
{
	return this->timer;
}

const InputManager& EngineSubSet::GetInputManager() const
{
	return this->inputmanager;
}

const Console& EngineSubSet::GetConsole() const
{
	return this->console;
}

const FPSCounter& EngineSubSet::GetFPSCounter() const
{
	return this->fpscounter;
}

const FontManager& EngineSubSet::GetFontManager() const
{
	return this->fontmanager;
}

const TextureSet& EngineSubSet::GetTextureSet() const
{
	return this->textureset;
}

const SkySphere& EngineSubSet::GetSkySphere() const
{
	return this->skysphere;
}

const EntityManager& EngineSubSet::GetEntityManager() const
{
	return this->entitymanager;
}

const ModelSet& EngineSubSet::GetModelSet() const
{
	return this->modelset;
}

const SceneManager& EngineSubSet::GetSceneManager() const
{
	return this->scenemanager;
}

const HeadsUpDisplay& EngineSubSet::GetHeadsUpDisplay() const
{
	return this->headsupdisplay;
}

const HeightMap& EngineSubSet::GetHeightMap() const
{
	return this->heightmap;
}

const ComplexMap& EngineSubSet::GetComplexMap() const
{
	return this->complexmap;
}
